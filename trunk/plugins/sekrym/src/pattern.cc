/*
** pattern.cc
** Login : <elthariel@localhost.localdomain>
** Started on  Sat Dec  2 06:33:07 2006 Elthariel
** $Id$
**
** Copyright (C) 2006 Elthariel
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

#include "pattern.hh"

Note            Pattern::&operator= (Note &src)
{
  this.m_note = src.m_note;
  this.m_vel = src.m_vel;
  return *this;
}

Pattern::Pattern(OutBus &a_outbus)
  :m_outbus(a_outbus), m_res(0)
{
  m_playing_note.vel = 0;
  m_playing_note.note = 0;
  clear();
}

void            Pattern::clear()
{
  int i;

  for (i = 0; i < PAT_SIZE; i++)
    {
      m_notes[i].m_note = PAT_DEF_NOTE;
      m_notes[i].m_vel = PAT_DEF_VEL;
    }
  m_res = PAT_DEF_RES;
  m_len = PAT_DEF_LEN;
  m_tick = 0;
  if (m_playing_note.vel > 0)
    end_playing();
}

void            Pattern::play(unsigned int a_tick_offset)
{
  unsigned char played;
  unsigned int new_tick;

  new_tick = m_tick + a_tick_offset;
  if (m_tick + a_tick_offset >= m_tick + m_res)
    {
      played = new_tick / m_res % m_len;
      play_note(played);
    }
  m_tick = new_tick % (m_len * m_res);
}

void            Pattern::end_playing()
{
  snd_seq_event_t ev;

  if (m_playing_note.vel > 0)
    {
      // FIXME set note off event.
      m_outbus.send(&ev);
    }
}

void            Pattern::play_note(unsigned char index)
{
  snd_seq_event_t ev;

  //FIXME fill note event.

  m_playing_note = m_notes[index];
  m_outbus.send(&ev);
  end_playing();
}

void            Pattern::stop()
{
  end_playing();
  m_tick = 0;
}

void            Pattern::set_res(unsigned char a_res)
{
  m_res = a_res;
}

void            Pattern::set_len(unsigned char a_len)
{
  m_len = a_len;
}
