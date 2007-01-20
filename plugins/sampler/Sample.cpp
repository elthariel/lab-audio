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
  : m_sr(sample_rate),
    amp_env(*EnvSwitch::create_switch_full(sample_rate, 170)),
    m_root_note(63), m_fine_pitch(0.0), m_gain(1.0), m_pan(1.0),
    m_norm(false),
    m_reverse(false)
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
   m_root_note(smp.m_root_note),
   m_fine_pitch(smp.m_fine_pitch), m_gain(smp.m_gain), m_pan(smp.m_pan),
   m_norm(smp.m_norm),
   m_reverse(smp.m_reverse),
   m_norm_factor(smp.m_norm_factor)
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

  sample_ratio = m_sr / ((float)info.samplerate) + m_fine_pitch;
  sample_ratio *= freq_table[voices[voice_number].freq] / freq_table[m_root_note];

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
                      + s(0, tmp + 1) * (1.0 - (voices[voice_number].pos - tmp)));
          outL[i] *= amp_env(voices[voice_number].pos_rel);
          if (info.channels == 1)
            {
              outR[i] += (s(0,tmp) * (voices[voice_number].pos - tmp)
                          + s(0, tmp + 1) * (1.0 - (voices[voice_number].pos - tmp)));
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

  for (int i = 0; i < sample_count; i++) // clear audio buffer
  {
  		outL[i] = 0.0;
  		outR[i] = 0.0;
  }

  for (i = 0; i < SAMPLER_POLY; i++) // play sample voice
    {
      if (voices[i].activated)
        {
          play_voice(i, sample_count, outL, outR);
        }
    }

  for (int i = 0; i < sample_count; i++) // Apply gain and pan
  {
  		outL[i] *= m_gain;
  		outR[i] *= m_gain;
      if (m_pan > 1.0)
        outL[i] *= m_pan - 1.0;
      else
        outR[i] *= m_pan - 1.0;
  }
  apply_antialias_filter(sample_count, outL, outR);
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

void                  Sample::set_root_note(char root)
{
  if (root >= 0)
    m_root_note = root;
}

void                  Sample::set_fine_pitch(double fine_pitch)
{
  m_fine_pitch = fine_pitch;
}

void                  Sample::set_gain(double gain)
{
  m_gain = gain;
}

void                  Sample::set_pan(double pan)
{
  m_pan = pan;
}

void                  Sample::apply_antialias_filter(unsigned int sample_count,
                                                     sample_t *outL,
                                                     sample_t *outR)
{
}

void                  Sample::normalize()
{
  unsigned int i;
  float max;

  if (!m_norm)
    {
      for (i = 0; i < info.channels; i++)
        {
          if (data[i] > max)
            max = data[i];
        }
      m_norm_factor = 1.0 / max;
      for (i = 0; i < info.channels; i++)
        {
          data[i] *= m_norm_factor;
        }
      m_norm = true;
    }
  else
    {
      for (i = 0; i < info.channels; i++)
        {
          data[i] /= m_norm_factor;
        }
      m_norm = false;
    }
}

void                    Sample::block_cpy(float *from, float *to)
{
  unsigned int          i;

  for (i = 0; i < info.channels; i++)
    to[i] = from[i];
}

void                    Sample::reverse()
{
  float                 *buf = new float[info.channels];
  unsigned int          size = info.frames / info.channels;
  unsigned int          i;

  for (i = 0; i < (size / 2); i++)
    {
      block_cpy(&data[i * info.channels], buf);
      block_cpy(&data[(size - i) * info.channels], &data[i * info.channels]);
      block_cpy(buf, &data[(size - i) * info.channels]);
    }
  m_reverse = !m_reverse;

}
