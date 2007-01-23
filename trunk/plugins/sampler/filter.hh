/*
** filter.hh
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

#ifndef   	FILTER_HH_
# define   	FILTER_HH_

#define         M_PI 3.14159265358979323846

class Filter
{
public:
  Filter(unsigned int sample_rate);
  virtual ~Filter(){}

  virtual void          set_cutoff(float cutoff);
  virtual void          set_res(float res);
  virtual void          apply(float *out) = 0;
protected:

  unsigned int          m_sr;
  float                 m_res;
  float                 m_cutoff;
};

class BesselLP24 : public Filter
{
public:
  BesselLP24(unsigned int sample_rate);
  virtual ~BesselLP24(){}

  virtual void          apply(float *out);
  virtual void          set_cutoff(float cutoff);
protected:
  float                 k, k2;
  float                 a0, a1, a2, a3, a4;
  float                 b0, b1, b2, b3, b4;
  float                 s0, s1, s2, s3;
  float                 input;
};


#endif	    /* !FILTER_HH_ */
