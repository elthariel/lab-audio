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

SmpVoice::SmpVoice(unsigned int m_sr)
  : activated(false), freq(0), vel(0), pos(0.0), pos_rel(0),
    note_off_pos_rel(0),
    filter_l(m_sr, 0, 22000., 0., 1),
    filter_r(m_sr, 0, 22000., 0., 1)
{
}

/*
 * Sample class implementation
 */

FrequencyTable 			Sample::freq_table = FrequencyTable();

Sample::Sample(string path, unsigned int sample_rate)
  : m_sr(sample_rate),
    aalias_l(sample_rate, 0, sample_rate / 2.0, 0.0, 2),
    aalias_r(sample_rate, 0, sample_rate / 2.0, 0.0, 2),
    amp_env(*EnvSwitch::create_switch_full(sample_rate, 170)),
    pitch_env(*EnvSwitch::create_switch_full(sample_rate, 170)),
    pitch_amount(0.0),
    pan_env(*EnvSwitch::create_switch_full(sample_rate, 170)),
    pan_amount(0.0),
    filter_env(*EnvSwitch::create_switch_full(sample_rate, 170)),
    filter_amount(0.0),
    voices(SAMPLER_POLY, SmpVoice(sample_rate)),
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
      m_antialias = true;
    }
  else
    cerr << "Unable to open : " << path << endl;

}

/*
 * This copy constructor is not up to date
 */
Sample::Sample(Sample &smp)
  :m_sr(smp.m_sr), info(smp.info),
   aalias_l(smp.aalias_l), aalias_r(smp.aalias_r),
   amp_env(*EnvSwitch::create_switch_full(smp.m_sr, 170)),
   pitch_env(*EnvSwitch::create_switch_full(smp.m_sr, 170)),
   pan_env(*EnvSwitch::create_switch_full(smp.m_sr, 170)),
   filter_env(*EnvSwitch::create_switch_full(smp.m_sr, 170)),
   m_root_note(smp.m_root_note),
   m_fine_pitch(smp.m_fine_pitch), m_gain(smp.m_gain), m_pan(smp.m_pan),
   m_norm(smp.m_norm),
   m_reverse(smp.m_reverse),
   m_norm_factor(smp.m_norm_factor)
{
  int           fcount = info.channels * info.frames;

  //FIXME copy env coefs.
  data = new sample_t[info.channels * info.frames];
  for (int i = 0; i < fcount; i++)
    {
      data[i] = smp.data[i];
    }
  m_antialias = smp.m_antialias;
}

Sample::~Sample()
{
  delete[] data;
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
  double                env;


  // Fill the output audio buffer
  while ((i < sample_count) && !sample_end)
    {
      // Aplly pitch env.
      if (voices[voice_number].freq >= 0)
        env = pitch_env(voices[voice_number].pos_rel, EnvModeOn);
      else
        env = pitch_env(voices[voice_number].pos_rel, EnvModeRelease);
      env *= pitch_amount;
      sample_ratio = m_sr / ((float)info.samplerate) + m_fine_pitch + env;
      sample_ratio *= freq_table[voices[voice_number].freq] / freq_table[m_root_note];

      // Is it the first sample of the sample ^^.
      if (voices[voice_number].pos == 0.0)
        {
          //cout << "Beginning of the sample" << endl;
          outL[i] = s(0,0);
          if (info.channels == 1)
            outR[i] = s(0,0);
          else
            outR[i] = s(0,0);
        }
      else
        {
          tmp = (unsigned int)voices[voice_number].pos;
          // Render sample at the right pitch
          outL[i] = (s(0,tmp) * (voices[voice_number].pos - tmp)
                      + s(0, tmp + 1) * (1.0 - (voices[voice_number].pos - tmp)));
          if (info.channels == 1)
            {
              outR[i] = (s(0,tmp) * (voices[voice_number].pos - tmp)
                          + s(0, tmp + 1) * (1.0 - (voices[voice_number].pos - tmp)));
            }
          else
            {
              outR[i] = (s(1,tmp) * (voices[voice_number].pos - tmp)
                          + s(1, tmp + 1) * (1.0 - (voices[voice_number].pos - tmp))) / 2;
            }
        }



      // Apply amp env.
      if (voices[voice_number].freq >= 0)
        env = amp_env(voices[voice_number].pos_rel, EnvModeOn);
      else
        {
          env = amp_env(voices[voice_number].pos_rel, EnvModeRelease);
          if (env == 0.0)
            {
              voices[voice_number].activated = false;
              sample_end = true;
            }
        }
      outL[i] *= env;
      outR[i] *= env;
      // Apply pan amp.
      /*      if (voices[voice_number].freq >= 0)
        env = pan_env(voices[voice_number].pos_rel, EnvModeOn) * pan_amount;
      else
        env = pan_env(voices[voice_number].pos_rel, EnvModeRelease) * pan_amount;
      outL[i] *= 1.0 - env;
      outR[i] *= env;*/


      // Update voice pos, check if it is the end of the sample
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
      outL[i] *= 1.0 - m_pan;
      outR[i] *= m_pan;
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

void                  Sample::set_fcut(double fcut)
{
  m_fcut = fcut;
}

void                  Sample::set_fres(double fres)
{
  m_fres = fres;
}

EnvSwitch             &Sample::env(EnvSelect which)
{
  switch (which)
    {
    case EnvAmp:
      return (amp_env);
      break;
    case EnvPitch:
      return (pitch_env);
      break;
    case EnvPan:
      return (pan_env);
      break;
    case EnvFilterCut:
      return (filter_env);
      break;
    }
}

double                &Sample::env_amount(EnvSelect which)
{
  switch (which)
    {
    case EnvPitch:
      return (pitch_amount);
      break;
    case EnvPan:
      return (pan_amount);
      break;
    case EnvFilterCut:
      return (filter_amount);
      break;
    }
}

void                  Sample::apply_antialias_filter(unsigned int sample_count,
                                                     sample_t *outL,
                                                     sample_t *outR)
{
  if (m_antialias)
    {
      aalias_l.filterout(outL, sample_count);
      aalias_r.filterout(outR, sample_count);
    }
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

void                    Sample::set_reverse(float val)
{
  bool tmp;

  if (val > 0.1)
    tmp = true;
  else
    tmp = false;

  if (tmp != m_reverse)
    {
      m_reverse = tmp;
      reverse();
    }
}

void                    Sample::set_normalize(float val)
{
  bool tmp;

  if (val > 0.0)
    tmp = true;
  else
    tmp = false;

  if (tmp != m_norm)
    {
      m_norm = tmp;
      normalize();
    }
}

void                    Sample::set_aalias(float val)
{
  bool tmp;

  if (val > 0.0)
    tmp = true;
  else
    tmp = false;
  m_antialias = tmp;
}

/*
 * Sample class : iSynth interface
 */
void                    Sample::play_note(const Seq::Note &a_note)
{
  note_on(a_note.note, a_note.vel);
}

void                    Sample::stop_note(const Seq::Note &a_note)
{
  note_on(a_note.note, a_note.vel);
}

void                    Sample::flush_note()
{
  unsigned int i;

  for (i = 0; i < SAMPLER_POLY; i++)
    voices[i].activated = false;
}


/*
 * TempBuffer singleton
 */

TempBuffer      *TempBuffer::m_instance = 0;

TempBuffer::TempBuffer()
{
}

float           *TempBuffer::get(bool sel)
{
  if (TempBuffer::m_instance == 0)
    m_instance = new TempBuffer();

    if (sel)
      return m_instance->buffers[0];
    else
      return m_instance->buffers[1];
}
