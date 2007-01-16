/*
** Sample.hh
** Login : <elthariel@localhost.localdomain>
** Started on  Thu Jan 11 04:09:37 2007 Elthariel
** $Id$
**
** Copyright (C) 2007 Elthariel
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

#ifndef   	SAMPLE_HH_
# define   	SAMPLE_HH_

#include <sndfile.h>

#include "Envelop.hh"

#define                 SAMPLER_POLY            32;

struct SmpVoice
{
  bool                  activated;
  double                freq;
  double                pos;
};



class Sample
{
private:
  unsigned int          m_sr; //Sample rate.

  double                *data;
  SF_INFO               info;
  SmpVoice              voices[SAMPLER_POLY];

  void                  load_data(SNDFILE *);
  void                  play_voice(unsigned int, unsigned int, double *);

public:
  Sample(Sample &smp);
  Sample(string, unsigned int);
  //  Sample(int);


  void                  render(unsigned int, double *);


};


#endif	    /* !SAMPLE_HH_ */
