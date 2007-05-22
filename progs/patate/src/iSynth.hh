/*
** iSynth.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Thu May 17 18:20:03 2007 Nahlwe
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

#ifndef   	ISYNTH_HH_
# define   	ISYNTH_HH_

#include "dsp_config.h"

namespace Dsp
{
  class iSynth
  {
  public:
    virtual ~iSynth(){}

    virtual void note_on(char note, char vel) = 0;
    virtual void note_off(char note, char vel) = 0;
    virtual void cc(unsigned int control, float value) = 0;
    virtual void reset() = 0;
    virtual void render(unsigned int sample_count,
                   unsigned int sample_rate,
                   unsigned int channel_count,
                   sample_t **out) = 0;
  };
};

#endif	    /* !ISYNTH_HH_ */
