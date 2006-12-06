/*
** sekrym.cc
** Login : <elthariel@localhost.localdomain>
** Started on  Sun Dec  3 09:54:31 2006 Elthariel
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

#include <iostream>
#include "sekrym.hh"

Sekrym::Sekrym(unsigned long sample_rate,
       const char* bundle_path,
       const LV2_Host_Feature** features)
  :LV2Plugin(2),
   m_outbus(*this, 1),
   m_free_pattern(m_outbus),
   m_pat(SEKRYM_PAT_COUNT, m_free_pattern),
   m_playing(false),
   m_sample_rate(sample_rate),
   m_remaining_samples(0.0),
   m_ticks(0),
   m_current_pattern(0),
   m_bpm(SEKRYM_DEFAULT_TEMPO),
   m_tick_res(SEKRYM_PPQ),
{
  clear();
}

Sekrym::~Sekrym()
{
}

void            Sekrym::run(uint32_t sample_count)
{
  float         samples_to_play;
  float         ticks
  unsigned int  ticks_int;

      samples_to_play = sample_count + m_remaining_samples;
      ticks = samples_to_play / m_tick_len;
      ticks_int = ticks;
      m_remaining_samples = (ticks - (float)ticks_int) * m_tick_len;
      m_ticks += ticks_int;
  if (m_playing)
    {
      m_pat[m_current_pattern].play(ticks_int);
    }
}

void            Sekrym::reset()
{
  m_remaining_samples = 0.0;
  m_ticks = 0;
}

void            Sekrym::play()
{
  m_playing = true;
}

void            Sekrym::stop()
{
  m_playing = false;
}

void            Sekrym::clear()
{
  int           i;

  for (i = 0; i < SEKRYM_PAT_COUNT; i++)
    m_pat[i].clear();
  m_current_pattern = 0;
}

void            Sekrym::set_bpm(uint32_t a_bpm)
{
  float         tick_len_second;
  float         sample_len;

  if (a_bpm)
    m_bpm = a_bpm;
  tick_len_second = (60.0 / ((float) m_bpm)) / m_tick_res;
  sample_len = 1.0 / (float) m_sample_rate;
  m_tick_len = tick_len_second / sample_len;
}
