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

# include <string>
# include <vector>
# include <sndfile.h>
# include <iSynth.hh>

# include "Envelop.hh"
# include "frequencytable.hpp"
# include "AnalogFilter.hpp"

# define                 SAMPLER_POLY            16

enum EnvSelect
  {
    EnvAmp,
    EnvPitch,
    EnvPan,
    EnvFilterCut,
    EnvFilterRes,
    EnvCount
  };

struct SmpVoice
{
  SmpVoice(unsigned int m_sr);
  bool                  activated;
  char                  freq;
  char                  vel;
  double                pos;    // pos in sample into the wav
  unsigned int          pos_rel; // pos in sample into the stream, relative to the start
  // time of this voice.
  unsigned int          note_off_pos_rel;
  AnalogFilter          filter_l;
  AnalogFilter          filter_r;
};


class Sample : public Seq::iSynth
{
public:
  Sample(Sample &smp);
  Sample(std::string, unsigned int);
  virtual ~Sample();
  //  Sample(int);

  typedef float         sample_t;

  void                  render(unsigned int, sample_t *, sample_t *);

  void                  note_on(char note_num, char velocity);
  void                  note_off(char note_num, char velocity);
  void                  set_root_note(char root);
  void                  set_fine_pitch(double fine_pitch);
  void                  set_gain(double gain);
  void                  set_pan(double pan);
  void                  set_fcut(double fcut);
  void                  set_fres(double fres);
  EnvSwitch             &env(EnvSelect);
  double                &env_amount(EnvSelect which);
  void                  set_reverse(float);
  void                  set_normalize(float);
  void                  set_aalias(float);
  void                  set_sample_rate(unsigned int a_sr);

  // iSynth interface
  virtual void          play_note(const Seq::Note &a_note);
  virtual void          stop_note(const Seq::Note &a_note);
  virtual void          flush_note();

private:
  // Internal data;
  unsigned int          m_sr; //Sample rate.

  sample_t              *data;
  SF_INFO               info;
  static FrequencyTable freq_table;
  AnalogFilter          aalias_l;
  AnalogFilter          aalias_r;

  //User config
  EnvSwitch             &amp_env;
  EnvSwitch             &pitch_env;
  double                pitch_amount;
  EnvSwitch             &pan_env;
  double                pan_amount;
  EnvSwitch             &filter_env;
  double                filter_amount;

  std::vector<SmpVoice> voices;
  char                  m_root_note;
  double                m_fine_pitch;
  double                m_gain;
  double                m_pan;
  double                m_fcut;
  double                m_fres;
  double                m_ftype;
  unsigned char         m_fstages;
  float                 m_norm_factor;
  bool                  m_norm;
  bool                  m_reverse;
  bool                  m_antialias;

  void                  load_data(SNDFILE *); //called by the constructor to load the sample.
  void                  play_voice(unsigned int, unsigned int, sample_t *, sample_t *);
  inline sample_t       &s(unsigned char a_chan, unsigned int a_pos);
  void                  apply_antialias_filter(unsigned int, sample_t *, sample_t *);
  void                  normalize();
  void                  reverse();
  inline void           block_cpy(float *from, float *to);

};

class                   TempBuffer
{
public:
  static float          *get(bool sel);

private:
  TempBuffer();

  static TempBuffer     *m_instance;

  float                 buffers[2][4096];
};

#endif	    /* !SAMPLE_HH_ */
