/*
** sampler.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Tue Apr 10 15:29:02 2007 Nahlwe
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

#ifndef   	SAMPLER_HH_
# define   	SAMPLER_HH_

#include <vector>
#include "Sample.hh"
#include <iSynth.hh>

class Sampler : public Seq::iSynthContainer
{
public:
  Sampler(unsigned int a_sample_count,
          unsigned int a_sample_rate);

  unsigned int          get_sample_count();
  Sample                *get_sample(unsigned int a_index);
  void                  set_sample_rate(unsigned int a_sr);
  virtual Seq::iSynth   *synth(unsigned int i);
protected:
  std::vector<Sample *> m_samples;
};

#endif	    /* !SAMPLER_HH_ */
