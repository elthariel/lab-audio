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
  : Filter(sample_rate),
    s0(0.0), s1(0.0), s2(0.0), s3(0.0)
{
}

void          BesselLP24::set_cutoff(float cutoff)
{
  Filter::set_cutoff(cutoff);

  k  = tan(M_PI * m_cutoff / m_sr);
  k2 = k*k; // speed improvement

  a0 =  ((((105*k + 105)*k + 45)*k + 10)*k + 1);
  a1 = -( ((420*k + 210)*k2        - 20)*k - 4);
  a2 = -(  (630*k2         - 90)*k2        + 6);
  a3 = -( ((420*k - 210)*k2        + 20)*k - 4);
  a4 = -((((105*k2- 105)*k + 45)*k - 10)*k + 1);

  b0 = 105*k2*k2;
  b1 = 420*k2*k2;
  b2 = 630*k2*k2;
  b3 = 420*k2*k2;
  b4 = 105*k2*k2;
}

void          BesselLP24::apply(float *out)
{
  input = *out;
  *out = b0 * input + s0;
  s0 = b1*input + a1/a0*(*out) + s1;
  s1 = b2*input + a2/a0*(*out) + s2;
  s2 = b3*input + a3/a0*(*out) + s3;
  s3 = b4*input + a4/a0*(*out);
  // FIXME For high speed substitude A1/A0 with A1' = A1/A0...
}
