/*
** 10tau.cpp
** Login : <elthariel@elthariel-desktop>
** Started on  Mon Jan 22 03:49:54 2007 Nahlwe
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
#include "10tau.hh"

using namespace std;

float                 Tau::f(float data)
{
  if (data > 0.0)
    {
      return (*(p<float>(peg_param_1)) -  data);
      //return (0.5 -  data);
    }
  else
    {
      return (data);
    }
}

Tau::Tau(uint32_t rate, const char*, const LV2_Host_Feature**)
  : LV2Plugin(peg_n_ports)
{

}

void            Tau::run(unsigned int sample_count)
{
  float         *inl, *inr, *outl, *outr;
  int i;

  inl = p<float>(peg_input_l);
  inr = p<float>(peg_input_r);
  outl = p<float>(peg_output_l);
  outr = p<float>(peg_output_r);

  for (i = 0; i < sample_count; i++)
    {
      /*      if ((outl[i] > 0.1) && (outl[i] < -0.1))
        outl[i] = f(inl[i]);
        else*/
      outl[i] = f(inl[i]);
      /*if ((outr[i] > 0.1) && (outr[i] < -0.1))
        outr[i] = f(inr[i]);
        else*/
      outr[i] = f(inr[i]);
    }
}

void initialise() __attribute__((constructor));
void initialise() {
  register_lv2<Tau>(peg_uri);
}
