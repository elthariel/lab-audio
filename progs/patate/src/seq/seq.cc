/*
** seq.cc
** Login : <elthariel@elthariel-desktop>
** Started on  Fri Apr 27 02:24:57 2007 Nahlwe
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
#include "seq.hh"

namespace Seq
{

  /*
   * Seq class
   */

  Seq::Seq(unsigned int a_bpm, unsigned int a_ppq,
           unsigned int a_part_count, unsigned int a_bar_count)
    : m_timer(a_bpm, a_ppq), m_parts(a_part_count),
      m_part_count(a_part_count),
      m_bar_count(a_bar_count), m_ppq(a_ppq), m_pos(0)
  {
    unsigned int i;

    for (i = 0; i < m_part_count; i++)
      m_parts[i] = new Part(a_ppq, 0, a_bar_count);
  }

  Seq::~Seq()
  {
    // FIXME delete parts.
  }

  void                  Seq::run()
  {
    unsigned int        ticks = m_timer.ticks();
    unsigned int        seq_len = m_bar_count * 4 * m_ppq;
    unsigned int        tmp;
    unsigned int        i;

    if (ticks > 0)
      {
        if ((m_pos + ticks) >= seq_len)
          {
            tmp = seq_len - m_pos;
            for (i = 0; i < m_part_count; i++)
              m_parts[i]->play(m_pos, tmp);
            m_pos = 0;
            tmp = ticks - tmp;
            if (tmp > 0)
              {
                for (i = 0; i < m_part_count; i++)
                  m_parts[i]->play(m_pos, tmp);
                m_pos += tmp;
              }
          }
        else
          {
            for (i = 0; i < m_part_count; i++)
              m_parts[i]->play(m_pos, ticks);
            m_pos += ticks;
          }
      }
  }

  Part                  &Seq::part(unsigned int part_id)
  {
    return *(m_parts[part_id]);
  }

  void                  Seq::set_bpm(unsigned int a_bpm)
  {
    m_timer.set_bpm(a_bpm);
  }

  void                  Seq::set_ppq(unsigned int a_ppq)
  {
    m_timer.set_ppq(a_ppq);
    m_ppq = a_ppq;
  }

  void                  Seq::start()
  {
    m_timer.start();
    m_pos = 0;

  }

  void                  Seq::pause()
  {
    m_timer.pause();
  }

  void                  Seq::stop()
  {
    m_timer.stop();
    m_pos = 0;
  }

  bool                  Seq::paused()
  {
    return m_timer.paused();
  }

  bool                  Seq::started()
  {
    return m_timer.started();
  }

};
