/*
** iOsc.cc
** Login : <elthariel@elthariel-desktop>
** Started on  Sun Jun  3 21:14:43 2007 Nahlwe
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
#include "dsp/iOsc.hh"

namespace Dsp
{
  /*
   * iOsc interface
   *   Generates signal sample per sample
   */

  iOsc::iOsc()
    : m_freq(400.0), m_sample_rate(44100)
  {
  }

  float           iOsc::frequency()
  {
    return m_freq;
  }

  void            iOsc::frequency(float new_freq)
  {
    m_freq = new_freq;
  }

  unsigned int    &iOsc::sampler_rate()
  {
    return m_sample_rate;
  }







  /*
   * iOscVector interface
   *   Generates a vector of samples of the buffer.
   */

  iOscVector::iOscVector()
    : m_freq(400.0), m_sample_rate(44100)
  {
  }

  float           iOscVector::frequency()
  {
    return m_freq;
  }

  void            iOscVector::frequency(float new_freq)
  {
    m_freq = new_freq;
  }


  unsigned int    &iOscVector::sampler_rate()
  {
    return m_sample_rate;
  }








  /*
   * iOscVectorAdapter
   */
  iOscVectorAdapter::iOscVectorAdapter(iOsc &a_osc)
    : m_osc(a_osc)
  {
  }

  iOscVectorAdapter::~iOscVectorAdapter()
  {
    delete &m_osc;
  }

  void            iOscVectorAdapter::reset()
  {
  }

  void            iOscVectorAdapter::render(float *out, unsigned int out_len)
  {
    unsigned int  i;

    for (i = 0; i < out_len; i++)
      out[i] += m_osc.sample();
  }

};

