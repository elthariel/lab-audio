/*
** patate.cpp
** Login : <elthariel@elthariel-desktop>
** Started on  Wed Apr  4 12:28:10 2007 Nahlwe
** $Id$
**
** Copyright (C) 2007 Nahlwe
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#include <iostream>
#include "patate.hh"
#include "part.hh"
#include "drumsynth.hh"

using namespace std;

static int      jack_process_proxy(jack_nframes_t nframes, void *arg)
{
  Patate        *instance = (Patate *)arg;

  return instance->process(nframes);
}

Patate::Patate(LFRingBufferWriter<Event> *a_writer,
               LFRingBufferReader<Event> *a_reader)
  : m_synths(16),
    m_seq(160, PATATE_SEQ_PPQ, PATATE_SAMPLER_COUNT, 1, m_synths),
    m_controller(*this, m_synths, m_seq, a_writer, a_reader),
    m_bpm(160)//, m_remaining_samples(0.0)
{
  unsigned int i;

  init_jack();
  m_seq.start();

  for(i = 0; i < 16; i++)
    {
      m_synths.synth(i, *new DspSynthAdapter(*new Dsp::DrumHat));
      cout << "synth " << i << " " << m_synths.synth(i);
    }
}

Patate::~Patate()
{
  close_jack();
}

void                  Patate::init_jack()
{

  // Opening jack connection
  m_jack_client = jack_client_new("Patate");
  if (m_jack_client == 0)
    throw *(new jack_error("Unable to connect to jack (servernot running ?)"));

  // Register process callback
  if (jack_set_process_callback(m_jack_client, &jack_process_proxy,
                            (void *)this))
    cerr << "Unable to register process callback" << endl;

  //Registering ports.
  m_midi_port_main = jack_port_register(m_jack_client, "midi_main",
                                   JACK_DEFAULT_MIDI_TYPE,
                                   JackPortIsInput, //| JackPortIsTerminal,
                                   0);
  if (m_midi_port_main == NULL)
    throw *(new jack_error("Unable to create Midi port"));

  m_midi_port_part = jack_port_register(m_jack_client, "midi_main",
                                   JACK_DEFAULT_MIDI_TYPE,
                                   JackPortIsInput, //| JackPortIsTerminal,
                                   0);
  if (m_midi_port_part == NULL)
    throw *(new jack_error("Unable to create Midi port"));

  m_midi_port_play = jack_port_register(m_jack_client, "midi_main",
                                   JACK_DEFAULT_MIDI_TYPE,
                                   JackPortIsInput, //| JackPortIsTerminal,
                                   0);
  if (m_midi_port_play == NULL)
    throw *(new jack_error("Unable to create Midi port"));

  m_audio_port_l = jack_port_register(m_jack_client, "outL",
                                      JACK_DEFAULT_AUDIO_TYPE,
                                      JackPortIsOutput | JackPortIsTerminal,
                                      0);
  if (m_audio_port_l == NULL)
    throw *(new jack_error("Unable to create Audio port"));

  m_audio_port_r = jack_port_register(m_jack_client, "outR",
                                      JACK_DEFAULT_AUDIO_TYPE,
                                      JackPortIsOutput | JackPortIsTerminal,
                                      0);
  if (m_audio_port_r == NULL)
    throw *(new jack_error("Unable to create Audio port"));


  m_buffer_size = jack_get_buffer_size(m_jack_client);

  //Activating client.
  if (jack_activate(m_jack_client))
    throw *(new jack_error("Unable to activate jack client"));
}

void            Patate::close_jack()
{
  jack_client_close(m_jack_client);
}

int             Patate::process(jack_nframes_t nframes)
{
  jack_nframes_t sample_rate;

  sample_rate = jack_get_sample_rate(m_jack_client);

  //Midi process
  process_midi(nframes);
  //Seq process
  process_seq(nframes, sample_rate);
  //Audio process
  process_audio(nframes, sample_rate);
}

void            Patate::process_audio(jack_nframes_t nframes,
                                      jack_nframes_t sample_rate)
{
  jack_default_audio_sample_t   *out[2];
  unsigned int                  i;

  out[0] = (jack_default_audio_sample_t *)jack_port_get_buffer(m_audio_port_l, nframes);
  out[1] = (jack_default_audio_sample_t *)jack_port_get_buffer(m_audio_port_r, nframes);

  for (i = 0; i < nframes; i++)
    {
      out[0][i] = 0.0;
      out[1][i] = 0.0;
    }
  for (i = 0; i < m_synths.get_synth_count(); i++)
    m_synths.synth(i)->render(nframes, sample_rate, 2,
                              (jack_default_audio_sample_t **)out);
}

void            Patate::process_midi(jack_nframes_t nframes)
{
  m_controller
    .process(nframes,
             jack_port_get_buffer(m_midi_port_main, nframes),
             jack_port_get_buffer(m_midi_port_part, nframes),
             jack_port_get_buffer(m_midi_port_play, nframes));
}

/*void            _process_event(Event &a_ev)
{
  Seq::Note     &note = *(new Seq::Note);

  // FIXME move to a PatateController.
  //cout << "received an event from gui or midi" << endl;
  if (a_ev.subsystem == Sys_DrumSeq)
    {
      if (a_ev.type == Event::TypeNote)
        {
          if (a_ev.data.note.note < 16)
            {
              note.note = 63;
              note.vel = a_ev.data.note.vel;
              note.len = 30;
              get_drumseq().part(1).add_step(note, 0, a_ev.data.note.note);
            }
          else if ((a_ev.data.note.note >= 16) && (a_ev.data.note.note < 32))
            get_drumseq().part(1).rem_step(0, a_ev.data.note.note - 16);
        }
    }
}*/

void            Patate::process_seq(jack_nframes_t nframes,
                                    jack_nframes_t sample_rate)
{
  /*  float         tick_len;
      float         sample_len;

      tick_len = 60.0 / (m_bpm * 4 * PATATE_SEQ_PPQ);
      sample_len = 1.0 / sample_rate;
      tick_len = tick_len / sample_len;

      m_remaining_samples += nframes;
      while (m_remaining_samples >= tick_len)
      {
      m_seq.tick();
      m_remaining_samples -= tick_len;
      }
  */
  unsigned int i;

  for (i = 0; i < 16; i++)
    m_seq.part(i).set_synth(m_synths.synth(i));
  m_seq.run();
}

void            Patate::set_bpm(unsigned int a_new_bpm)
{
  m_bpm = a_new_bpm;
  m_seq.set_bpm(a_new_bpm);
}

unsigned int    Patate::get_bpm()
{
  return m_bpm;
}

SynthManager    &Patate::get_synths()
{
  return m_synths;
}

Seq::Seq        &Patate::get_drumseq()
{
  return m_seq;
}



/*
 * Exception
 */
jack_error::jack_error(const char *a_err)
  : m_err(a_err)
{
}

const char *jack_error::what() const throw()
{
  return m_err;
}
