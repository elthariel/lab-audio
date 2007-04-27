/*
** mapping.cpp
** Login : <elthariel@elthariel-desktop>
** Started on  Tue Apr  3 19:37:23 2007 Nahlwe
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
#include "mapping.hh"

using namespace std;

template <class OutType>
void    Mapping<OutType>::set_out(LFRingBufferWriter<OutType> *a_out)
{
  m_outs.clear();
  m_outs.push_back(a_out);
}

template <class OutType>
void    Mapping<OutType>::add_out(LFRingBufferWriter<OutType> *a_out)
{
  m_outs.push_back(a_out);
}

template <class OutType>
void    Mapping<OutType>::rem_out(LFRingBufferWriter<OutType> *a_out)
{
  m_outs.remove(a_out);
}

template <class OutType>
void    Mapping<OutType>::send(OutType &a_ev)
{
  typename list<Out *>::iterator    iter;

  for (iter = m_outs.begin(); iter != m_outs.end(); iter++)
    (*iter)->write(&a_ev);
}

bool            AseqNoMap::accept(kEvent &a_ev)
{
  if (a_ev.type != kEvent::kNote)
    return false;

  snd_seq_ev_clear(&m_buf);

  if (a_ev.data.note.vel == 0)
    {
      snd_seq_ev_set_noteoff(a_ev, 0, a_ev.data.note.note,
                             a_ev.data.note.vel)
    }
  else
    {
      snd_seq_ev_set_noteon(a_ev, 0, a_ev.data.note.note,
                            a_ev.data.note.vel)
    }
  send(a_ev);
  return true;
}
