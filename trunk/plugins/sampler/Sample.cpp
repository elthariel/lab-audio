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

/*
 * SmpVoice Implementation
 */

SmpVoice::SmpVoice()
  : activated(false), freq(0), vel(0), pos(0.0), pos_rel(0)
{
}

/*
 * Sample class implementation 
 */

FrequencyTable 			Sample::freq_table = FrequencyTable();

Sample::Sample(string path, unsigned int sample_rate)
  : m_sr(sample_rate), m_root_note(50),
    amp_env(*EnvSwitch::create_switch_full(sample_rate, 170))
{
  SNDFILE       *file;

  file = sf_open(path.c_str(), SFM_READ, &this->info);
  sf_command (file, SFC_SET_NORM_FLOAT, NULL, SF_TRUE) ;
  if (file)
    {
      load_data(file);
      sf_close(file);
    }
  else
    cerr << "Unable to open : " << path << endl;

}

Sample::Sample(Sample &smp)
  :m_sr(smp.m_sr), info(smp.info),
   amp_env(*EnvSwitch::create_switch_full(smp.m_sr, 170)),
   m_root_note(smp.m_root_note)
{
  int           fcount = info.channels * info.frames;

  data = new sample_t[info.channels * info.frames];
  for (int i = 0; i < fcount; i++)
    {
      data[i] = smp.data[i];
    }
}

void                    Sample::load_data(SNDFILE *file)
{
  int                   fcount;

  data = new sample_t[info.channels * info.frames];
  fcount = sf_readf_float(file, data, info.frames);
  if (fcount < 1)
    {
      cout << "Unable to read data of the sample" << endl;
    }
  else if (fcount != info.frames)
    {
      cout << "Unable to read full data sample, or library error" << endl;
    }
  else
  	cout << "Load sample, channels = " << info.channels << ",\tsample rate " << info.samplerate << endl;
}

void                    Sample::play_voice(unsigned int voice_number,
                                           unsigned int sample_count,
                                           sample_t *outL, sample_t *outR)
{
  float                 sample_ratio;
  int                   tmp;
  bool                  sample_end = false;
  int                   i = 0;

  sample_ratio = m_sr / ((float)info.samplerate);
  sample_ratio *= 1 + freq_table[voices[voice_number].freq] - freq_table[m_root_note];

  //cout << "Play a voice : " << sample_ratio << "" << endl;
  while ((i < sample_count) && !sample_end)
    {
      if (voices[voice_number].pos == 0.0)
        {
          cout << "Beginning of the sample" << endl;
          outL[i] += s(0,0);
          if (info.channels == 1)
            outR[i] += s(0,0);
          else
            outR[i] += s(0,0);
        }
      else
        {
          tmp = (unsigned int)voices[voice_number].pos;
          outL[i] += (s(0,tmp) * (voices[voice_number].pos - tmp)
                      + s(0, tmp + 1) * (1.0 - (voices[voice_number].pos - tmp))) / 2;
          outL[i] *= amp_env(voices[voice_number].pos_rel);
          if (info.channels == 1)
            {
              outR[i] += (s(0,tmp) * (voices[voice_number].pos - tmp)
                          + s(0, tmp + 1) * (1.0 - (voices[voice_number].pos - tmp))) / 2;
        	}
          else
            {
              outR[i] += (s(1,tmp) * (voices[voice_number].pos - tmp)
                          + s(1, tmp + 1) * (1.0 - (voices[voice_number].pos - tmp))) / 2;
            }
		  outR[i] *= amp_env(voices[voice_number].pos_rel);	
        }
      voices[voice_number].pos_rel++;
      voices[voice_number].pos += sample_ratio;
      if (voices[voice_number].pos >= (info.frames / info.channels))
        {
          voices[voice_number].activated = false;
          sample_end = true;
        }
    //cout << "OutL \t" << outL[i] << "\tOutR \t" << outR[i] << endl;
    i++;
    }
}

void                    Sample::render(unsigned int sample_count,
                                       sample_t *outL, sample_t *outR)
{
  int i;

  for (int i = 0; i < sample_count; i++)
  {
  		outL[i] = 0.0;
  		outR[i] = 0.0;
  }
  
  for (i = 0; i < SAMPLER_POLY; i++)
    {
      if (voices[i].activated)
        {
          play_voice(i, sample_count, outL, outR);
        }
    }
}

void                    Sample::note_on(char note_num, char velocity)
{
  bool                  finished = false;
  int                   i = 0;

  while ((i < SAMPLER_POLY) && !finished)
    {
      if (!voices[i].activated)
        {
          voices[i].activated = true;
          voices[i].freq = note_num;
          voices[i].vel = velocity;
          voices[i].pos = 0.0;
          voices[i].pos_rel = 0;
          finished = true;
        }
      i++;
    }
}

void                    Sample::note_off(char note_num, char velocity)
{
  bool                  finished = false;
  int                   i = 0;

  while((i < SAMPLER_POLY) &&!finished)
    {
      if (voices[i].activated &&
          voices[i].freq == note_num &&
          voices[i].vel == velocity)
        {
          voices[i].activated = false;
          finished = true;
        }
      i++;
    }
}

Sample::sample_t     	&Sample::s(unsigned char a_chan, unsigned int a_pos)
{
  return (data[info.channels * a_pos + a_chan]);
}
