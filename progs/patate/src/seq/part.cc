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
  Part::Part(unsigned int a_ppq, iSynth *a_synth,
             unsigned int a_seq_len, int a_res)
    : m_synth(a_synth), m_seq_len(a_seq_len),
      m_res(a_res), m_ppq(a_ppq)
  {
  }

  Part::~Part()
  {
    // FIXME delete all Note;
  }

  void                          Part::play(unsigned int a_pos,
                                           unsigned int a_tick)
  {
    std::list<Note *>::iterator iter;

    if (m_synth)
      {
        update_note_on(a_tick);
        for (iter = m_seq.begin();
             ((*iter)->start < (a_pos + a_tick)) && (iter != m_seq.end());
             iter++)
          if ((*iter)->start >= a_pos)
            {
              insert_note_on(*iter);
              m_synth->play_note(**iter);
            }
      }
  }

  void                          Part::flush()
  {
    std::list<Note *>::iterator iter;

    if (m_synth)
      for (iter = m_note_on.begin(); iter != m_note_on.end(); iter++)
        m_synth->stop_note(**iter);
    m_note_on.clear();
  }

  void                          Part::add_note(Note &a_note)
  {
    std::list<Note *>::iterator iter;

    for (iter = m_seq.begin();
         ((*iter)->start <= a_note.start) && (iter != m_seq.end());
         iter++);
    m_seq.insert(iter, &a_note);
  }

  bool                          Part::rem_note(unsigned int a_begin,
                                               unsigned int a_end)
  {
    std::list<Note *>::iterator iter;
    Note                        *to_rem = 0;

    if (!a_end)
      a_end == a_begin;

    if (m_synth)
      for (iter = m_seq.begin();
           ((*iter)->start > a_end) && (iter != m_seq.end());
           iter++)
        {
          if (to_rem)
            {
              m_seq.remove(to_rem);
              to_rem = 0;
            }
          if (((*iter)->start >= a_begin) && ((*iter)->start <= a_end))
            to_rem = *iter;
        }
    if (to_rem)
      m_seq.remove(to_rem);
  }

  const std::list<Note *>       &Part::get_seq() const
  {
    return m_seq;
  }

  void                          Part::set_mres(int a_res)
  {
    m_res = a_res;
  }

  void                          Part::set_synth(iSynth *a_synth)
  {
    m_synth = a_synth;
  }

  void                          Part::update_note_on(unsigned int a_tick)
  {
    std::list<Note *>::iterator iter;
    bool                        to_del = false;

    for (iter = m_note_on.begin(); iter != m_note_on.end(); iter++)
      {
        if (to_del)
          {
            m_note_on.pop_front();
            to_del = false;
          }
        if ((*iter)->rem >= a_tick)
          {
            to_del = true;
            if (m_synth)
              m_synth->stop_note(**iter);
          }
        else
          (*iter)->rem -= a_tick;
      }
    if (to_del)
      m_note_on.pop_front();
  }

  void                          Part::insert_note_on(Note *a_note)
  {
    std::list<Note *>::iterator iter;

    if (a_note)
      {
        for (iter = m_note_on.begin();
             ((*iter)->start <= a_note->start) && (iter != m_note_on.end());
             iter++);
        m_note_on.insert(iter, a_note);
      }
  }

void                        Part::add_step(Note &a_note,
                                           unsigned int a_bar,
                                           unsigned int a_step)
{
  unsigned int pos = a_bar * 4 * m_ppq + a_step * (m_ppq / 4);
  a_note.start = pos;
  add_note(a_note);
}

void                        Part::rem_step(unsigned int a_bar,
                                           unsigned int a_step)
{
  unsigned int pos_start = a_bar * 4 * m_ppq + a_step * (m_ppq / 4);
  unsigned int pos_end = a_bar * 4 * m_ppq + (a_step + 1) * (m_ppq / 4);
  rem_note(pos_start, pos_end);
}



};
