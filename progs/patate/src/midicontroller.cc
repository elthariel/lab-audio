/*
** midicontroller.cc
** Login : <elthariel@elthariel-desktop>
** Started on  Sat May 19 18:42:13 2007 Nahlwe
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
#include "midicontroller.hh"
#include "seq/seq.hh"
#include "seq/part.hh"

using namespace std;

MidiController::MidiController(SynthManager &a_synths,
                 Seq::Seq &a_seq,
                 LFRingBufferWriter<Event> *a_writer,
                 LFRingBufferReader<Event> *a_reader)
  : m_writer(a_writer),
    m_reader(a_reader),
    m_synths(a_synths),
    m_seq(a_seq)
{
}

void            MidiController::process(jack_nframes_t nframes,
                                        void *a_midi_main,
                                        void *a_midi_part,
                                        void *a_midi_play)
{
  process_midi_port(nframes, a_midi_main, Sys_Main);
  process_midi_port(nframes, a_midi_part, Sys_Part);
  process_midi_port(nframes, a_midi_play, Sys_Play);
  process_gui();
}

void            MidiController::process_event(Event &a_ev)
{
  if (a_ev.subsystem == Sys_Main)
    process_main(a_ev);
  else if (a_ev.subsystem == Sys_Part)
    process_part(a_ev);
  else if (a_ev.subsystem == Sys_Play)
    process_play(a_ev);
}

bool            MidiController::midi_to_event(jack_midi_event_t &a_midi,
                                              Event &a_ev)
{
  // FIXME
  return false;
}

void            MidiController::process_midi_port(jack_nframes_t nframes,
                                                  void *a_midi_buffer,
                                                  SubSystem a_sys)
{
  jack_midi_event_t     midi_ev;
  jack_nframes_t        ev_count, i;
  Event                 ev;

  ev.subsystem = a_sys;
  ev_count = jack_midi_get_event_count(a_midi_buffer, nframes);
  for (i = 0; i < ev_count; i++)
    {
      if (jack_midi_event_get(&midi_ev, a_midi_buffer, i, nframes) == 0)
        {
          if (midi_to_event(midi_ev, ev))
            process_event(ev);
        }
    }
}

void            MidiController::process_gui()
{
  Event         ev;

  while(m_reader->ready())
    {
      m_reader->read(&ev);
      process_event(ev);
    }
}

/*
 * play subsystem's events are just relayed to concerned synths.
 */
void            MidiController::process_play(Event &a_ev)
{
  if (a_ev.type == Event::TypeNote)
    {
      Seq::Note note;
      note.note = a_ev.data.note.note;
      note.vel = a_ev.data.note.vel;
      if (a_ev.data.note.on)
        m_synths.synth(a_ev.data.note.chan)->play_note(note);
      else
        m_synths.synth(a_ev.data.note.chan)->stop_note(note);
    }
  else if (a_ev.type == Event::TypeCtrl)
    {
      m_synths.synth(a_ev.data.ctrl.chan)->cc(a_ev.data.ctrl.ctrl,
                                              a_ev.data.ctrl.val / 127.0);
    }
}

/*
 * Main event are dispatched to correspond function which will do the job.
 */
void            MidiController::process_main(Event &a_ev)
{
  if (a_ev.type == Event::TypeNote)
    {
      switch(a_ev.data.note.note)
        {
        case 0: case 1: case 2: case 3: case 4: case 5:
          main_transport(a_ev);
          break;
        default:
          cout << "This midi message is no assigned" << endl;
          break;
        }
    }
  else if (a_ev.type == Event::TypeCtrl)
    {
      switch(a_ev.data.ctrl.ctrl)
        {
        case 0: case 1: case 2: case 3:
          main_tempo(a_ev);
          break;
        default:
          cout << "This midi message is no assigned" << endl;
          break;
        }
    }
}

/*
 * Part event are dispatched to correspond function which will do the job.
 */

void            MidiController::process_part(Event &a_ev)
{
  if (a_ev.type == Event::TypeNote)
    {
      switch(a_ev.data.note.note)
        {
        case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
        case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15:
          part_step(a_ev);
          break;
        case 16: case 17: case 18: case 19: case 20: case 21:
          part_menu(a_ev);
          break;
        default:
          cout << "This midi message is no assigned" << endl;
          break;
        }
    }
  else if (a_ev.type == Event::TypeCtrl)
    {
      switch(a_ev.data.ctrl.ctrl)
        {
        default:
          cout << "This midi message is no assigned" << endl;
          break;
        }
    }
}

void                    MidiController::main_transport(Event &a_ev)
{
}

void                    MidiController::main_tempo(Event &a_ev)
{
}

void                    MidiController::part_step(Event &a_ev)
{
  if (a_ev.data.note.on)
    {
      Seq::Note         &note = *new Seq::Note();
      note.note = 63;
      note.vel = 127;
      note.len = 24;
      m_seq.part(a_ev.data.note.chan).add_step(note, 0, a_ev.data.note.note);
    }
  else
    {
      m_seq.part(a_ev.data.note.chan).rem_step(0, a_ev.data.note.note);
    }
}

void                    MidiController::part_menu(Event &a_ev)
{
}
