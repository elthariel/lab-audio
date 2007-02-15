//
// adelay.hpp for adelay in /home/elthariel/code/lab-audio/plugins/adelay
//
// Copyright 2007 BALLET Julien
// Login   <elthariel@lse.epita.fr>
//
// Started on  Wed Feb  7 09:02:49 2007 Nahlwe
// Last update Tue Feb 13 08:10:14 2007 Nahlwe
//

#ifndef ADELAY_HPP_
# define ADELAY_HPP_

//# include "lv2plugin.hpp"
# include "lv2instrument.hpp"
# include "adelay.peg"

// TAPE length in ms
# define        TAPE_SIZE       2000

class ADelay : public LV2Instrument
{
public:
  ADelay(uint32_t rate, const char*, const LV2_Host_Feature**);
  ~ADelay();
  void          run(uint32_t sample_count);
  void          activate();

protected:
  void          dispatch_control();
  void          compute_rate();

  // Internals data.
  unsigned int  m_sr;
  unsigned int  m_pcount;
  unsigned int  m_tape_size; //tape len in sample.
  float         *m_tape_l, *m_tape_r;
  float         m_head, m_rate;

  // Controls
  float         m_tempo, m_time_sw, m_time_ms, m_time_beat;
  float         m_feedback, m_amount;
};

#endif
