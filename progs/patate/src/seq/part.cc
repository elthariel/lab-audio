/*
** part.cc
** Login : <elthariel@elthariel-desktop>
** Started on  Thu Apr 26 12:51:35 2007 Nahlwe
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
#include "part.hh"


using namespace std;

namespace Seq
{

  /*
   * Note struct
   */
  Note::Note()
    : note(0), vel(0), start(0),
      len(0), rem(0)
  {
    unsigned int i;

    for (i = 0; i < NOTE_PARAMS; i++)
      param[i] = 0.0;
  }






  /*
   * Part class
   */
  Part::Part(unsigned int a_part_index, unsigned int a_seq_len,
             int a_res)
    : m_part_index(a_part_index),
      m_seq_len(a_seq_len),
      m_res(a_res)
  {
    m_note_sequence.connect(MasterEventBus::get()[a_part_index]);
    m_cc_sequence.connect(MasterEventBus::get()[a_part_index]);
  }

  Part::~Part()
  {
    m_note_sequence.clear();
    m_cc_sequence.clear();
  }

  /// \todo interleaves event to respect order
  void                          Part::play(tick a_pos,
                                           tick a_tick)
  {
    m_cc_sequence.play(a_pos, a_tick);
    m_note_sequence.play(a_pos, a_tick);
  }

  void                          Part::flush()
  {
    m_note_sequence.clear();
    m_cc_sequence.clear();
  }

  /// \todo handle note adding or removing
  void                          Part::add_note(Event a_note, tick a_pos)
  {
  }

  /// \todo handle note adding or removing
  bool                          Part::rem_note(tick a_begin,
                                               tick a_end)
  {
  }

  void                          Part::set_mres(int a_res)
  {
    m_res = a_res;
  }

  /// \todo handle note adding or removing
  void                        Part::add_step(Note &a_note,
                                             unsigned int a_bar,
                                             unsigned int a_step)
  {
    unsigned int ppq = TimerSingleton::get().ppq();
    unsigned int pos = a_bar * 4 * ppq + a_step * (ppq / 4);

  }

  /// \todo handle note adding or removing
  void                        Part::rem_step(unsigned int a_bar,
                                             unsigned int a_step)
  {
    unsigned int ppq = TimerSingleton::get().ppq();
    unsigned int pos_start = a_bar * 4 * ppq + a_step * (ppq / 4);
    unsigned int pos_end = a_bar * 4 * ppq + (a_step + 1) * (ppq / 4);

  }

  void                        Part::connect(EventBus<Event> &a_event_bus)
  {
    m_note_sequence.connect(&a_event_bus);
    m_cc_sequence.connect(&a_event_bus);
  }

};
