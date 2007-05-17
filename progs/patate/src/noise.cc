/*
** noise.cc
** Login : <elthariel@elthariel-desktop>
** Started on  Tue May 15 18:48:57 2007 Nahlwe
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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <cmath>
#include "noise.hh"

using namespace std;

namespace Dsp
{
/*
 * URandom
 */

int URandom::m_fd = 0;
bool URandom::m_write = false;

URandom::URandom(const char *path)
{
  if (m_fd == 0)
    {
      m_fd = open(path, O_RDWR);
      if (m_fd < 0)
        {
          cout << "Could not open urandom device for rw : " << strerror(errno) << endl;
          m_fd = open(path, O_RDONLY);
          if (m_fd < 0)
            {
              cout << "Could not open urandom device for read : " << strerror(errno) << endl
                   << "White noise generators won't work" << endl;
        }
        }
      else
        m_write = true;
    }
}

void            URandom::seed(char *a_seed, unsigned int a_len)
{
  if (m_write)
    write(m_fd, (void *)a_seed, a_len);
}

uint32_t        URandom::make_uint32()
{
  uint32_t      res;

  read(m_fd, (void *)&res, sizeof(uint32_t));
  return (res);
}

int32_t         URandom::make_int32()
{
  int32_t       res;

  read(m_fd, (void *)&res, sizeof(int32_t));
  return (res);
}

float           URandom::make_float()
{
  int32_t       rd;
  float         res;

  rd = make_int32();
  res = ((float)rd) / 2147483647.0;
  return (res);
}

double          URandom::make_double()
{
  return make_float();
}








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
    out[i] = m_osc.sample();
}










/*
 * WhiteNoise class
 */

void            WhiteNoise::reset()
{
}

float           WhiteNoise::sample()
{
  return m_rand.make_float();
}

WhiteNoise::WhiteNoise(iRand &a_rand)
  : m_rand(a_rand)
{
}










/*
 * GaussianWhiteNoise class
 */

GaussianWhiteNoise::GaussianWhiteNoise(iRand &a_rand)
  : m_rand(a_rand)
{
}

void            GaussianWhiteNoise::reset()
{
}

/*
 * Algorithm from Steven W. Smith:
 *  The Scientist and Engineer's Guide to Digital Signal Processing
 *  http://www.dspguide.com
 */
float           GaussianWhiteNoise::sample()
{
  float         rnd[2];

  rnd[0] = m_rand.make_float();
  rnd[1] = m_rand.make_float();

  return ((float) sqrt(-2.0f * log(rnd[0])) * cos(2.0f * PI * rnd[1]));
}

};






