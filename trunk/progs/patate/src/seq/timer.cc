/*
** timer.cc
** Login : <elthariel@elthariel-desktop>
** Started on  Thu Apr 26 10:53:33 2007 Nahlwe
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
#include <cstdlib>
#include <cstdio>
#include "timer.hh"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

namespace Seq
{

  Timer::Timer(unsigned int a_bpm, unsigned int a_ppq, unsigned int a_sr)
    : m_bpm(a_bpm), m_ppq(a_ppq), m_sample_rate(a_sr),
      m_samples(0)
  {
    update_tick_len();
  }

  void                  Timer::set_ppq(unsigned int a_ppq)
  {
    m_ppq = a_ppq;
    update_tick_len();
  }

  void                  Timer::set_bpm(unsigned int a_bpm)
  {
    m_bpm = a_bpm;
    update_tick_len();
  }

  uint64_t              Timer::samples()
  {
    return m_samples;
  }

  void                  Timer::samples_elapsed(unsigned int frames)
  {
    m_samples += frames;
  }

  uint64_t              Timer::ticks()
  {
    return (m_samples * m_tick_len);
  }

  void                  Timer::update_tick_len()
  {
    double              sample_len;
    double              tick_len;

    sample_len = 1.0 / m_sample_rate;
    tick_len = 60.0 / (m_bpm * m_ppq);
    m_tick_len = tick_len / sample_len;
  }
};
