/*
** filter.cpp
** Login : <elthariel@elthariel-desktop>
** Started on  Sat Jan 20 12:41:26 2007 Nahlwe
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

#include <math.h>

#include "filter.hh"

/*
 * Filter class implementation.
 */

Filter::Filter(unsigned int sample_rate)
  :m_sr(sample_rate), m_res(0), m_cutoff(22000.0)
{
}

void          Filter::set_cutoff(float cutoff)
{
  m_cutoff = cutoff;
}

void          Filter::set_res(float res)
{
  m_res = res;
}

/*
 * BesselLP24 class Implementation
 */

BesselLP24::BesselLP24(unsigned int sample_rate)
  : Filter(sample_rate)
{
}

void          BesselLP24::apply(unsigned int sample_count, float *outL, float *outR)
{
  float K  = tan(M_PI * m_cutoff / m_sr);
  float K2 = K*K; // speed improvement

  float A0 =  ((((105*K + 105)*K + 45)*K + 10)*K + 1);
  float A1 = -( ((420*K + 210)*K2        - 20)*K - 4);
  float A2 = -(  (630*K2         - 90)*K2        + 6);
  float A3 = -( ((420*K - 210)*K2        + 20)*K - 4);
  float A4 = -((((105*K - 105)*K + 45)*K - 10)*K + 1);

  float B0 = 105*K2*K2;
  float B1 = 420*K2*K2;
  float B2 = 630*K2*K2;
  float B3 = 420*K2*K2;
  float B4 = 105*K2*K2;

  //Per sample calculate:
  float State0R = 0.0;
  float State0L = 0.0;
  float State1R = 0.0;
  float State1L = 0.0;
  float State2R = 0.0;
  float State2L = 0.0;
  float State3R = 0.0;
  float State3L = 0.0;
  float InputL, InputR;
  for (unsigned int i = 0; i < sample_count; i++)
    {
      InputL = outL[i];
      outL[i] = B0*InputL                + State0L;
      State0L = B1*InputL + A1/A0*outL[i] + State1L;
      State1L = B2*InputL + A2/A0*outL[i] + State2L;
      State2L = B3*InputL + A3/A0*outL[i] + State3L;
      State3L = B4*InputL + A4/A0*outL[i];

      InputR = outR[i];
      outR[i] = B0*InputR                + State0R;
      State0R = B1*InputR + A1/A0*outR[i] + State1R;
      State1R = B2*InputR + A2/A0*outR[i] + State2R;
      State2R = B3*InputR + A3/A0*outR[i] + State3R;
      State3R = B4*InputR + A4/A0*outR[i];
    }

  // FIXME For high speed substitude A1/A0 with A1' = A1/A0...
}
