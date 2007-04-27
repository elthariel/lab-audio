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

#include <vector>
#include "sampler.hh"

# define    DPATTERN_LEN 256
# define    DPATTERN_COUNT 16

struct drum_note
{
  char          vel;
  // FIXME add modifiers.
};

struct drum_pattern
{
  drum_pattern();
  drum_note     data[DPATTERN_LEN];
};

class DrumPattern
{
public:
  DrumPattern(unsigned int a_ppq, Sampler &a_sampler,
              unsigned int a_track_id);
  void                  tick();
protected:
  DrumPattern();
  void                  play_note(unsigned int a_index);

  Sampler               &m_sampler;
  drum_pattern          m_pattern;
  unsigned int          m_track_id;
  unsigned int          m_ppq;
  unsigned int          m_res;
  unsigned int          m_len;
  unsigned int          m_tick;
  unsigned int          m_index;
  char                  m_note;
  drum_note             m_active_note;
};

class DrumSeq
{
public:
  DrumSeq(unsigned int a_ppq, Sampler &a_sampler);
  void                  tick();
protected:

  Sampler                       &m_sampler;
  std::vector<DrumPattern *>    m_patterns;
};

#endif	    /* !DRUMSEQ_HH_ */
