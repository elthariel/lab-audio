/*
** midicontroller.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Sat May 19 18:39:53 2007 Nahlwe
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

#ifndef   	MIDICONTROLLER_HH_
# define   	MIDICONTROLLER_HH_

#include <jack/jack.h>
#include <jack/midiport.h>
#include "lfringbuffer.hh"
#include "event.hh"
#include "synth_manager.hh"
#include "seq.hh"

class Patate;

class MidiController
{
public:
  MidiController(Patate& a_patate,
                 SynthManager &a_synths,
                 Seq::Seq &a_seq,
                 LFRingBufferWriter<Event> *a_writer,
                 LFRingBufferReader<Event> *a_reader);
  void                  process(jack_nframes_t nframes,
                                void *a_midi_main,
                                void *a_midi_part,
                                void *a_midi_play);
  void                  process_event(Event &a_ev);
protected:
  void                  process_gui();
  bool                  midi_to_event(jack_midi_event_t &a_midi,
                                      Event &a_ev);
  void                  process_midi_port(jack_nframes_t nframes,
                                          void *a_midi_buffer,
                                          SubSystem a_sys);


  void                  process_main(Event &a_ev);
  void                  process_part(Event &a_ev);
  void                  process_play(Event &a_ev);

  /*
   * Main events handlers.
   */
  void                  main_transport(Event &a_ev);
  void                  main_tempo(Event &a_ev);
  //void                  main_(Event &a_ev);

  /*
   * Part events handlers.
   */
  void                  part_step(Event &a_ev);
  void                  part_menu(Event &a_ev);
  //void                  part_(Event &a_ev);

  LFRingBufferWriter<Event>     *m_writer; // to the gui
  LFRingBufferReader<Event>     *m_reader; // from the gui
  Patate                        &m_patate;
  SynthManager                  &m_synths;
  Seq::Seq                      &m_seq;
};

#include "patate.hh"

#endif	    /* !MIDICONTROLLER_HH_ */
