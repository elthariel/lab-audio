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
#include "timer.hh"

using namespace std;

namespace Seq
{

  Timer::Timer(unsigned int a_bpm, unsigned int a_ppq,
               clockid_t a_clock)
    : m_bpm(a_bpm), m_ppq(a_ppq), m_clock(a_clock),
      m_started(false), m_paused(false), m_ticks(0),
      m_remaining_nsec(0)
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

  void                  Timer::start()
  {
    m_started = true;
    clock_gettime(m_clock, &m_last_tick);
  }

  void                  Timer::pause()
  {
    // FIXME simplis pause
    if (m_paused)
      {
        m_paused = false;
        start();
      }
    else
      m_paused = true;

  }

  void                  Timer::stop()
  {
    m_started = false;
  }

  bool                  Timer::paused()
  {
    return m_paused;
  }

  bool                  Timer::started()
  {
    return m_started;
  }

  unsigned int          Timer::ticks()
  {
    unsigned int        res;

    update_ticks();
    res = m_ticks;
    m_ticks = 0;
  }

  void                  Timer::update_tick_len()
  {
    double              len;

    // FIXME doesn't support tick_len > 1s;
    len = 60.0 / ((double)m_bpm * m_ppq);
    m_tick_len.tv_sec = 0;
    if (len >= 1.0)
      m_tick_len.tv_nsec = (long) len;
    else
      {
        len = 1000000000.0;
        m_tick_len.tv_nsec = (long) len;
      }
  }

  void                  Timer::update_ticks()
  {
    unsigned int        tmp;
    timespec            now;

    // FIXME doesn't support tick_len > 1s;
    clock_gettime(m_clock, &now);
    tmp = now.tv_sec - m_last_tick.tv_sec;
    tmp *= 1000000000;
    tmp += now.tv_nsec - m_last_tick.tv_nsec;
    tmp += m_remaining_nsec;

    m_ticks += tmp / m_tick_len.tv_nsec;
    m_remaining_nsec = tmp % m_tick_len.tv_nsec;
    m_last_tick = now;
  }

};
