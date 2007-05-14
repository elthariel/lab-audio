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

#include <iostream>
#include "sampler.hh"

using namespace std;

Sampler::Sampler(unsigned int a_sample_count,
                 unsigned int a_sample_rate)
  : m_samples(a_sample_count, 0)
{
  unsigned int i;

  for (i = 0; i < a_sample_count; i++)
    m_samples[i] = new Sample("/home/elthariel/test.wav",
                              a_sample_rate);
}

unsigned int    Sampler::get_sample_count()
{
  return m_samples.size();
}

Sample          *Sampler::get_sample(unsigned int a_index)
{
  if (a_index > m_samples.size())
    return 0;
  else
    return m_samples[a_index];
}

Seq::iSynth     *Sampler::synth(unsigned int i)
{
  return get_sample(i);
}

void            Sampler::set_sample_rate(unsigned int a_sr)
{
  vector<Sample *>::iterator iter;

  for (iter = m_samples.begin(); iter != m_samples.end(); iter++)
    if (*iter)
      (*iter)->set_sample_rate(a_sr);
}


