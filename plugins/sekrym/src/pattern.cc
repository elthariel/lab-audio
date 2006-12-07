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
  :m_outbus(a_outbus), m_res(0),
{
  m_playing_note.vel = 0;
  m_playing_note.note = 0;
  clear();
  stop();
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
  if (m_playing_note.vel > 0)
    end_playing();
}

void            Pattern::play(unsigned int a_tick_offset)
{
  unsigned char played;
  unsigned int new_tick;

  if (m_last_played < 0)
    play_note(0);

  new_tick = m_tick + a_tick_offset;
  if (new_tick >= m_last_played * m_res)
    {
      played = new_tick / m_res % m_len;
      play_note(played);
    }
  m_tick = new_tick % (m_len * m_res);
}

void            Pattern::end_playing()
{

  if (m_playing_note.vel > 0)
    {
      // FIXME set note off event.
      m_outbus.send(&ev);
    }
}

void            Pattern::play_note(unsigned char index)
{
  m_last_played = index;

  //FIXME fill note event.
  if (m_playing_note.vel < 0)
    {
      if (m_pat[index].vel == 0)
        end_playing();
      else
        {
          if (m_pat[index].note != m_playing_note.note)
            {
              if (m_pat[index].vel > 0)
                m_outbus.send_note_on(m_pat[index].note, m_pat[index].vel);
              else
                m_outbus.send_note_on(m_pat[index].note, 0 - m_pat[index].vel);
              end_playing();
            }
        }
    }
  else
    {
      if (m_playing_note.vel != 0)
        {
          end_playing();
        }
      if (m_pat[index].vel)
        {
          if (m_pat[index].vel > 0)
            m_outbus.send_note_on(m_pat[index].note, m_pat[index].vel);
          else
            m_outbus.send_note_on(m_pat[index].note,
                                  0 - m_pat[index].vel);
        }
    }

  m_playing_note = m_pat[index];
}

void            Pattern::stop()
{
  end_playing();
  m_tick = 0;
  m_last_played = -1;
}

void            Pattern::set_res(unsigned char a_res)
{
  m_res = a_res;
}

void            Pattern::set_len(unsigned char a_len)
{
  m_len = a_len;
}
