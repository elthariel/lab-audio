/*
** drumseq.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Wed Apr  4 00:00:29 2007 Nahlwe
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

#ifndef   	DRUMSEQ_HH_
# define   	DRUMSEQ_HH_

# define    DPATTERN_LEN 128
# define    DPATTERN_COUNT 16

struct drum_note
{
  char          vel;
  // FIXME add modifiers.
};

struct drum_pattern
{
  drum_note     data[DPATTERN_LEN];
};

class DrumPattern
{
public:
  DrumPattern(LV2Instrument &a_plugin,
              unsigned int a_ppq);
  void                  tick();
protected:
  DrumPattern();

  LV2Instrument         &m_plugin;
  drum_pattern          &m_pattern;
  unsigned int          m_ppq;
  unsigned int          m_res;
  unsigned int          m_len;
  unsigned int          m_tick;
};

#endif	    /* !DRUMSEQ_HH_ */
