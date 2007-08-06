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

  Seq::~Seq()
  {
    unsigned int i;

    for (i = 0; i < m_part_count; i++)
      if(m_parts[i])
        delete m_parts[i];
  }

  void                  Seq::run(Transport::Position &a_pos, Transport::Position &a_len)
  {
    unsigned int        i;

    for (i = 0; i < m_part_count; i++)
      if (m_parts[i])
        m_parts[i]->play(a_pos, a_len);
  }

  Part                  &Seq::part(unsigned int part_id)
  {
    return *(m_parts[part_id]);
  }
};
