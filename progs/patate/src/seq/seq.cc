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

using namespace std;

namespace Seq
{

  /*
   * Seq class
   */

  Seq::Seq(unsigned int a_part_count)
    : m_parts(a_part_count),
      m_part_count(a_part_count)
  {
    unsigned int i;

    for (i = 0; i < m_part_count; i++)
      m_parts[i] = new Part(i, 1);

    TransportSingleton::get().signal_played().connect(sigc::mem_fun(*this, &Seq::run));
  }

  ///  \todo delete parts
  Seq::~Seq()
  {
  }

  ///  \todo run the sequencer
  void                  Seq::run(Transport::Position &a_pos, Transport::Position &a_len)
  {

    //    cout << "tranport_pos (bars-beats-ticks) \t" << a_pos.bars << " \t" << a_pos.beats << " \t" << a_pos.ticks << endl;
    //    cout << a_len.bars << " \t" << a_len.beats << " \t" << a_len.ticks << endl;

    /*    unsigned int        ticks = m_timer.ticks();
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
        //        cout << ticks << " : " << m_pos << endl;
        }*/
  }

  Part                  &Seq::part(unsigned int part_id)
  {
    return *(m_parts[part_id]);
  }
};
