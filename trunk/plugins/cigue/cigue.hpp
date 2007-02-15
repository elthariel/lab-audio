//
// atropos.hpp for atropos in /home/elthariel/code/lab-audio/plugins/atropos
//
// Copyright 2007 BALLET Julien
// Login   <elthariel@lse.epita.fr>
//
// Started on  Wed Feb  7 09:02:49 2007 Nahlwe
// Last update Thu Feb 15 05:55:25 2007 Nahlwe
//

#ifndef ATROPOS_HPP_
# define ATROPOS_HPP_

# include <wef.hh>
//# include "lv2plugin.hpp"
# include "lv2instrument.hpp"
# include "cigue.peg"
# include "AnalogFilter.hpp"
# include "frequencytable.hpp"

# define        SEND_TRACK_COUNT        4
# define        STEREO_TRACK_COUNT      16

class Cigue : public LV2Instrument
{
public:
  Cigue(uint32_t rate, const char*, const LV2_Host_Feature**);
  void          run(uint32_t sample_count);
  void          activate();

protected:
  void          process_midi(unsigned int sample_count);
  void          dispatch_control();

  unsigned int  m_sr;
  unsigned int  m_pcount;

  FrequencyTable m_freqs;
  AnalogFilter  m_aalias;
  AnalogFilter  m_filter;
  AnalogFilter  m_filter2;
  Wef           m_saw;
  Wef           m_square;
  Wef           m_exp;
  bool          m_wave; // true = saw, false = square.
  float         m_pos;
  float         m_cur_rate;
  float         m_target_rate;
  float         m_rate_inc;
  unsigned int  m_note_count;
  bool          m_glide_on;

  char          m_note, m_vel;
  float         m_note_len;
  float         m_cutoff;
  float         m_pitch;
  float         m_res;
  float         m_env_mod;
  float         m_env_decay;
  float         m_glide;
  float         m_dist;
};

#endif
