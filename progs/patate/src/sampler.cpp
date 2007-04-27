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

Sampler::Sampler(unsigned int a_sample_count)
  : m_samples(a_sample_count, 0)
{
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
