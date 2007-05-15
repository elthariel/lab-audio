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

using namespace std;

static int      jack_process_proxy(jack_nframes_t nframes, void *arg)
{
  Patate        *instance = (Patate *)arg;

  return instance->process(nframes);
}

Patate::Patate(LFRingBufferWriter<Event> *a_writer,
               LFRingBufferReader<Event> *a_reader)
  : m_writer(a_writer),
    m_reader(a_reader),
    m_sampler(PATATE_SAMPLER_COUNT, 48000),
    m_seq(160, PATATE_SEQ_PPQ, PATATE_SAMPLER_COUNT, 1, m_sampler),
    m_bpm(160)//, m_remaining_samples(0.0)
{
  init_jack();
  m_seq.start();
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
  m_midi_port = jack_port_register(m_jack_client, "midi_in",
                                   JACK_DEFAULT_MIDI_TYPE,
                                   JackPortIsInput, //| JackPortIsTerminal,
                                   0);
  if (m_midi_port == NULL)
    throw *(new jack_error("Unable to create Midi_in port"));

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
  //Internal event process.
  process_event();
  //Seq process
  process_seq(nframes, sample_rate);
  //Audio process
  process_audio(nframes, sample_rate);
}

void            Patate::process_audio(jack_nframes_t nframes,
                                      jack_nframes_t sample_rate)
{
  jack_default_audio_sample_t   *outL, *outR;
  unsigned int                  i;

  outL = (jack_default_audio_sample_t *)jack_port_get_buffer(m_audio_port_l, nframes);
  outR = (jack_default_audio_sample_t *)jack_port_get_buffer(m_audio_port_r, nframes);
  for (i = 0; i < m_sampler.get_sample_count(); i++)
    m_sampler.synth(i)->render(nframes, sample_rate, outL, outR);
}

void            Patate::process_midi(jack_nframes_t nframes)
{
  void                  *midi_buf;
  jack_midi_event_t     ev;
  jack_nframes_t        ev_count, i;

  midi_buf = jack_port_get_buffer(m_midi_port, nframes);
  ev_count = jack_midi_get_event_count(midi_buf, nframes);
  for (i = 0; i < ev_count; i++)
    {
      if (jack_midi_event_get(&ev, midi_buf, i, nframes) == 0)
        cerr << "Received a midi event" << endl;
    }
}

void            Patate::process_event()
{
  Event         ev;

  while(m_reader->ready())
    {
      m_reader->read(&ev);
      _process_event(ev);
    }
}

void            Patate::_process_event(Event &a_ev)
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
              note.note = a_ev.data.note.note;
              note.vel = a_ev.data.note.vel;
              note.len = 300;
              get_drumseq().part(1).add_step(note, 0, a_ev.data.note.note);
            }
          else if ((a_ev.data.note.note >= 16) && (a_ev.data.note.note < 32))
            get_drumseq().part(1).rem_step(0, a_ev.data.note.note - 16);
        }
    }
}

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
  m_seq.run();
}

void            Patate::set_bpm(unsigned int a_new_bpm)
{
  m_bpm = a_new_bpm;
}

Sampler         &Patate::get_sampler()
{
  return m_sampler;
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
