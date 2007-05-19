/*
** varinoise.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Thu May 17 16:16:38 2007 Nahlwe
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

#ifndef   	VARINOISE_HH_
# define   	VARINOISE_HH_

#include "noise.hh"
#include "dsp_config.h"
#include "iFilter.hh"

namespace Dsp
{
  class VariNoise : public iOscVector
  {
  public:
    VariNoise(iOscVector &a_osc);
    virtual ~VariNoise();

    virtual void          reset();
    virtual void          frequency(float new_frew);
    virtual void          render(sample_t *out, unsigned int out_len);
  protected:
    OnePoleFilter         m_filter;
    iOscVector            &m_osc;
  };

};

#endif	    /* !VARINOISE_HH_ */
