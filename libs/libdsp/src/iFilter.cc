/*
** iFilter.cc
** Login : <elthariel@elthariel-desktop>
** Started on  Thu May 17 14:26:58 2007 Nahlwe
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
#include <cmath>
#include "dsp/iFilter.hh"

namespace Dsp
{
/*
 * iFilterVector interface
 */

iFilterVector::iFilterVector()
  :m_sample_rate(44100), m_cutoff(11000.0),
   m_resonance(0.0)
{

}

iFilterVector::~iFilterVector()
{
}

void            iFilterVector::cutoff(float frequency)
{
  m_cutoff = frequency;
}

void            iFilterVector::resonance(float q)
{
  m_resonance = q;
}

float           iFilterVector::cutoff()
{
  return m_cutoff;
}

float           iFilterVector::resonance()
{
  return m_resonance;
}

unsigned int    &iFilterVector::sample_rate()
{
  return m_sample_rate;
}








/*
 * OnePoleFilter Class
 *   Algo from mistert at inwind dot com
 *   http://www.musicdsp.org/archive.php?classid=3#117
 */
OnePoleFilter::OnePoleFilter()
  : m_type(LpFilter)
{
  m_state[0] = 0.0;
  m_state[1] = 0.0;
  m_state[2] = 0.0;
  compute_coefs();
}

void            OnePoleFilter::cutoff(float frequency)
{
  m_cutoff = frequency;
  compute_coefs();
}

void            OnePoleFilter::resonance(float q)
{
  m_resonance = q;
  compute_coefs();
}

void            OnePoleFilter::apply(sample_t *out,
                                     unsigned int out_len)
{
  unsigned int  i;

  for (i = 0; i < out_len; i++)
    {
      m_state[0] = out[1];

      out[i] = out[1] * m_coefs[0]
        + m_state[1] * m_coefs[1]
        + m_state[2] * m_coefs[2];

      m_state[1] = m_state[0];
      m_state[2] = out[i];
    }
}

void            OnePoleFilter::type(Type a_type)
{
  m_type = a_type;
  compute_coefs();
}

void            OnePoleFilter::compute_coefs()
{
  float w = 2.0 * m_sample_rate;
  float norm, cut;

  if (m_type == LpFilter)
    {
      cut = m_cutoff * 2.0 * M_PI;
      norm = 1.0 / (cut + w);
      m_coefs[2] = (w - cut) * norm;
      m_coefs[0] = m_coefs[0] = cut * norm;
    }
  else
    {
      cut = m_cutoff * 2.0 * M_PI;
      norm = 1.0 / (cut + w);
      m_coefs[0] = w * norm;
      m_coefs[1] = -m_coefs[0];
      m_coefs[2] = (w - cut) * norm;
    }
}

};

/*
void SetLPF(float fCut, float fSampling)
{
  float w = 2.0 * fSampling;
  float Norm;

  fCut *= 2.0F * PI;
  Norm = 1.0 / (fCut + w);
  b1 = (w - fCut) * Norm;
  a0 = a1 = fCut * Norm;
}

void SetHPF(float fCut, float fSampling)
{
    float w = 2.0 * fSampling;
    float Norm;

    fCut *= 2.0F * PI;
    Norm = 1.0 / (fCut + w);
    a0 = w * Norm;
    a1 = -a0;
    b1 = (w - fCut) * Norm;
}
*/
