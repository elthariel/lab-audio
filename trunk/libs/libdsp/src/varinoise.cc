/*
** varinoise.cc
** Login : <elthariel@elthariel-desktop>
** Started on  Thu May 17 16:18:07 2007 Nahlwe
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
#include "dsp/VariNoise.hh"

namespace Dsp
{
/*
 * VariNoise class
 */
VariNoise::VariNoise(iOscVector &a_osc)
  : m_osc(a_osc)
{
  frequency(0.0);
}

VariNoise::~VariNoise()
{
}

void          VariNoise::reset()
{
  m_freq = 0.0;
}

void          VariNoise::frequency(float new_frew)
{
  m_freq = new_frew;
  if (m_freq > 0.0)
    {
      m_filter.type(OnePoleFilter::HpFilter);
      m_filter.cutoff(m_sample_rate / 2);
    }
  else if (m_freq < 0.0)
    {
      m_filter.type(OnePoleFilter::LpFilter);
      m_filter.cutoff(20.0);
    }
}

void          VariNoise::render(sample_t *out, unsigned int out_len)
{
  unsigned int i;
  float amount;
  sample_t buf[out_len];

  m_osc.render(out, out_len);

  for (i = 0; i < out_len; i++)
    buf[i] = out[i];

  m_filter.apply(buf, out_len);

  if (m_freq < 0.0)
    amount = -m_freq;
  else
    amount = m_freq;

  for (i = 0; i < out_len; i++)
    out[i] = (1.0 - amount) * out[i] + amount * buf[i];
}

};

