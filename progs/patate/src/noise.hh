/*
** noise.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Tue May 15 18:48:49 2007 Nahlwe
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

#ifndef   	NOISE_HH_
# define   	NOISE_HH_

# include "dsp_config.h"

#define PI 3.1415926536f

namespace Dsp
{

class iRand
{
public:
  virtual ~iRand(){}

  virtual void          seed(char *a_seed, unsigned int a_len) = 0;
  virtual uint32_t      make_uint32() = 0;
  virtual int32_t       make_int32() = 0;
  virtual float         make_float() = 0;
  virtual double        make_double() = 0;

private:
};

class URandom : public iRand
{
public:
  URandom(const char *path = "/dev/urandom");
  ~URandom(){}
  void          seed(char *a_seed, unsigned int a_len);
  uint32_t      make_uint32();
  int32_t       make_int32();
  float         make_float();
  double        make_double();
protected:
  static int    m_fd;
  static bool   m_write;

};

class iOsc
{
public:
  iOsc();
  virtual ~iOsc(){}

  virtual void          reset() = 0;
  virtual float         frequency();
  virtual void          frequency(float new_frew);
  virtual unsigned int  &sampler_rate();
  virtual sample_t      sample() = 0;
protected:
  float                 m_freq;
  unsigned int          m_sample_rate;
};

class iOscVector
{
public:
  iOscVector();
  virtual ~iOscVector(){}

  virtual void          reset() = 0;
  virtual float         frequency();
  virtual void          frequency(float new_frew);
  virtual unsigned int  &sampler_rate();
  virtual void          render(sample_t *out, unsigned int out_len) = 0;

protected:
  float                 m_freq;
  unsigned int          m_sample_rate;
};

class iOscVectorAdapter : public iOscVector
{
public:
  iOscVectorAdapter(iOsc &a_osc);
  ~iOscVectorAdapter();

  virtual void          reset() = 0;
  virtual void          render(sample_t *out, unsigned int out_len) = 0;
protected:
  iOsc                  &m_osc;
};

class WhiteNoise : public iOsc
{
public:
  WhiteNoise(iRand &a_rand);
  virtual void          reset();
  virtual sample_t      sample();
protected:
  iRand                 &m_rand;
};

class GaussianWhiteNoise : public iOsc
{
public:
  GaussianWhiteNoise(iRand &a_rand);
  virtual void          reset();
  virtual sample_t      sample();
protected:
  iRand                 &m_rand;
};

};




#endif	    /* !NOISE_HH_ */
