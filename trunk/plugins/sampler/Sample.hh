/*
** Sample.hh
** Login : <elthariel@localhost.localdomain>
** Started on  Thu Jan 11 04:09:37 2007 Elthariel
** Part of Promethee
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

#include <string>
#include <sndfile.h>

#include "Envelop.hh"
#include "frequencytable.hpp"

#define                 SAMPLER_POLY            32


struct SmpVoice
{
  SmpVoice();
  bool                  activated;
  char                  freq;
  char                  vel;
  double                pos;    // pos in sample into the wav
  unsigned int          pos_rel; // pos in sample into the stream, relative to the start
  // time of this voice.
};


class Sample
{
public:
  Sample(Sample &smp);
  Sample(std::string, unsigned int);
  //  Sample(int);

  typedef float         sample_t;

  void                  render(unsigned int, sample_t *, sample_t *);

  void                  note_on(char note_num, char velocity);
  void                  note_off(char note_num, char velocity);
  void                  set_root_note(char root);
  void                  set_fine_pitch(double fine_pitch);
  void                  set_gain(double gain);
  void                  set_pan(double pan);

private:
  // Internal data;
  unsigned int          m_sr; //Sample rate.

  sample_t              *data;
  SF_INFO               info;
  static FrequencyTable freq_table;

  //User config
  EnvSwitch             &amp_env;

  SmpVoice              voices[SAMPLER_POLY];
  char                  m_root_note;
  double                m_fine_pitch;
  double                m_gain;
  double                m_pan;          //
  float                 m_norm_factor;
  bool                  m_norm;
  bool                  m_reverse;

  void                  load_data(SNDFILE *); //called by the constructor to load the sample.
  void                  play_voice(unsigned int, unsigned int, sample_t *, sample_t *);
  inline sample_t       &s(unsigned char a_chan, unsigned int a_pos);
  void                  apply_antialias_filter(unsigned int, sample_t *, sample_t *);
  void                  normalize();
  void                  reverse();
  inline void           block_cpy(float *from, float *to);

};


#endif	    /* !SAMPLE_HH_ */
