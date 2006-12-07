/*
** pattern.hh
** Login : <elthariel@localhost.localdomain>
** Started on  Sat Dec  2 03:28:17 2006 Elthariel
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

#ifndef   	PATTERN_HH_
# define   	PATTERN_HH_

# include "sequence.hh"

# define PAT_SIZE       32
# define PAT_DEF_NOTE   0 //FIXME choose a note we'll hear in most case
# define PAT_DEF_VEL    100
# define PAT_DEF_RES    16
# define PAT_DEF_LEN    16

struct Note
{
  char  m_note;         // value of the note.
  char  m_vel;          // velocity of the note.

  Note  &operator= (Note &src);
};

class Pattern : public Sequence
{
protected:
  Note                  m_notes[PAT_SIZE];
  Note                  m_playing_note;

  int                   m_last_played;

public:
  Pattern(OutBus &a_outbus);

  virtual void          clear();
  virtual void          play(unsigned int a_tick_offset = 1);
  virtual void          set_res(unsigned char a_res);
  virtual void          set_len(unsigned char a_len);

  void                  play_note(unsigned char index);
  void                  end_playing();
};

#endif	    /* !PATTERN_HH_ */
