/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
//
// Class: beatsmasher
//
// Created by: GESTES Cedric <ctaf42@gmail.com>
// Created on: Mon Jan  29 19:34:17 2007
//
#include <iostream>
#include "beatsmasher.h"


BeatSmasher::BeatSmasher(int samplerate) {
  m_samplerate = samplerate;
  m_buffer = new float[samplerate];
  m_active = false;
  m_pos = 0;
  m_pos_learn = 0.;
  m_loop_size = 3000;
}

void BeatSmasher::active(const bool active) {
  m_active = active;
  if (m_active) {
    m_pos = 0;
    m_pos_learn = 0.;
  }
}

void BeatSmasher::learn(float *buffer, const int samplecount) {
  int i = 0;
  for (;m_pos_learn < m_samplerate; ++m_pos_learn) {
    m_buffer[m_pos_learn] = buffer[i];
    ++i;
    if (i >= samplecount)
      break;
  }
  if (m_pos_learn < m_loop_size)
    m_pos = m_pos_learn;
}

void BeatSmasher::process(float *buffer,const int samplecount) {
  int i = 0, j = 0, endsz, prevpos;
  if (!m_active)
    return;
  prevpos = m_pos_learn;
  //load internal buffer
  learn(buffer, samplecount);

  if (m_pos_learn < m_loop_size)
    return;

  if (m_pos_learn > m_loop_size && prevpos < m_loop_size) {
    i = m_loop_size - prevpos;
  }

  //copy from the
  for (; i < samplecount; ++i) {
    buffer[i] = m_buffer[m_pos];
    ++m_pos;
    if (m_pos > m_loop_size) {
      m_pos = 0;
    }
  }
}

