/*
** iOsc.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Sun Jun  3 21:12:36 2007 Nahlwe
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

#ifndef   	IOSC_HH_
# define   	IOSC_HH_

# include "dsp_config.h"

namespace Dsp
{
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

    virtual void          reset();
    virtual void          render(sample_t *out, unsigned int out_len);
  protected:
    iOsc                  &m_osc;
  };

};

#endif	    /* !IOSC_HH_ */
