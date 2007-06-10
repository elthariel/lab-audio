/*
** iFilter.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Thu May 17 14:19:27 2007 Nahlwe
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

#ifndef   	IFILTER_HH_
# define   	IFILTER_HH_

#include        "dsp_config.h"

namespace Dsp
{

class iFilterVector
{
public:
  iFilterVector();
  virtual ~iFilterVector();

  virtual void          cutoff(float frequency);
  virtual void          resonance(float q);
  virtual float         cutoff();
  virtual float         resonance();
  virtual unsigned int  &sample_rate();

  virtual void          apply(sample_t *out,
                              unsigned int out_len) = 0;

protected:
  unsigned int          m_sample_rate;
  float                 m_cutoff;
  float                 m_resonance;
};

class OnePoleFilter : public iFilterVector
{
public:
  enum Type
    {
      LpFilter,
      HpFilter
    };

  OnePoleFilter();
  virtual ~OnePoleFilter(){}

  virtual void          cutoff(float frequency);
  virtual void          resonance(float q);
  virtual void          apply(sample_t *out,
                              unsigned int out_len);
  void                  type(Type a_type);
protected:
  void                  compute_coefs();

  Type                  m_type;
  float                 m_coefs[3]; // a0, a1, b1
  sample_t              m_state[3]; // in[n]. in[n-1], out[n]
};

};

#endif	    /* !IFILTER_HH_ */
