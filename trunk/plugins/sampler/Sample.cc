/*
** Sample.cc
** Login : <elthariel@localhost.localdomain>
** Started on  Thu Jan 11 04:15:16 2007 Elthariel
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

#include <iostream>
#include "Sample.hh"

using namespace std;

Sample::Sample(string path, unsigned int sample_rate)
  : m_sr(sample_rate)
{
  SNDFILE       *file;

  file = sf_open(path.c_str(), SFM_READ, &this->info);
  if (file)
    {
      load_data(file);
      sf_close(file);
    }
  else
    cerr << "Unable to open : " << path << endl;

}

Sample::Sample(Sample &smp)
  :m_sr(smp.m_sr), info(smp.info)
{
  int           fcount = info.channels * info.frames;

  data = new double[info.channels * info.frames];
  for (int i = 0; i < fcount; i++)
    {
      data[i] = smp.data[i];
    }
}

void                    Sample::load_data(SNDFILE *file)
{
  int                   fcount;

  data = new double[info.channels * info.frames];
  fcount = sf_readf_double(file, data, info.frames);
  if (fcount < 1)
    {
      cout << "Unable to read data of the sample" << endl;
    }
  else if (fcount != info.frames)
    {
      cout << "Unable to read full data sample, or library error" << endl;
    }
}

void                    Sample::play_voice(unsigned int voice_number,
                                           unsigned int sample_count,
                                           double *out)
{
}

void                    Sample::render(unsigned int sample_count, double *out)
{
  int i;

  for (i = 0; i < SAMPLER_POLY; i++)
    {
      if (voice[i].activated)
        {
          play_voice(i, sample_count, out);
        }
    }
}
