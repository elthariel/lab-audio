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

#include <iostream>
#include "drumseq.hh"

using namespace std;

/*
 * Drum pattern
 */

DrumPattern::DrumPattern(unsigned int a_ppq, Sampler &a_sampler,
                         unsigned int a_track_id)
  :m_sampler(a_sampler), m_track_id(a_track_id),
   m_ppq(a_ppq), m_res(a_ppq), m_len(16), m_tick(0),
   m_index(0), m_note(67)
{
  m_active_note.vel = 0;
}

/*DrumPattern::DrumPattern()
{
}*/

void            DrumPattern::tick()
{
  m_tick++;
  if (m_tick >= m_res)
    {
      play_note(m_index);
      m_index += 1;
      m_index %= m_len;
      m_tick -= m_res;
    }
}

void            DrumPattern::play_note(unsigned int a_index)
{
  Sample        *sample;

  sample = m_sampler.get_sample(m_track_id);
  if (sample)
    {
      if (m_pattern.data[a_index].vel > 0)
        {
          if (m_active_note.vel > 0)
            sample->note_off(m_note, m_active_note.vel);
          sample->note_on(m_note, m_pattern.data[a_index].vel);
          m_active_note.vel = m_pattern.data[a_index].vel;
        }
    }
}

/*
 * Drum sequencer
 */

DrumSeq::DrumSeq(unsigned int a_ppq, Sampler &a_sampler)
  : m_sampler(a_sampler),
    m_patterns(a_sampler.get_sample_count(), 0)
{
  unsigned int i;

  for (i = 0; i < m_patterns.size(); i++)
    m_patterns[i] = new DrumPattern(a_ppq, a_sampler, i);
}

void                    DrumSeq::tick()
{
  unsigned int          i;

  for (i = 0; i < m_patterns.size(); i++)
    m_patterns[i]->tick();
}

/*
 * drum_pattern
 */

drum_pattern::drum_pattern()
{
  unsigned int i;

  for (i = 0; i < DPATTERN_LEN; i++)
    {
      data[i].vel = 0;
    }
}
