//
// atropos.cpp for atropos in /home/elthariel/code/lab-audio/plugins/atropos
//
// Copyright 2007 BALLET Julien
// Login   <elthariel@lse.epita.fr>
//
// Started on  Wed Feb  7 09:03:52 2007 Nahlwe
// Last update Thu Feb 15 10:51:47 2007 Nahlwe
//

#include <iostream>
#include "adelay.peg"
#include "adelay.hpp"
#include "lv2-midifunctions.h"
#include <cmath>

using namespace std;

ADelay::ADelay(uint32_t rate, const char*,
               const LV2_Host_Feature**)
  : LV2Instrument(peg_n_ports), m_sr(rate),
    m_head(0.), m_rate(1.),
    m_tape_size((TAPE_SIZE / 1000) * m_sr),
    m_tape_l(0), m_tape_r(0),
    m_tempo(180), m_time_sw(1),
    m_time_ms(200.), m_time_beat(3.),
    m_feedback(0.3), m_amount(1.)
{
  unsigned int i;

  m_tape_l = new float[m_tape_size];
  m_tape_r = new float[m_tape_size];
  for (i = 0; i < m_tape_size; i++)
    {
      m_tape_l[i] = 0.0;
      m_tape_r[i] = 0.0;
    }
}

ADelay::~ADelay()
{
  delete[] m_tape_l;
  delete[] m_tape_r;
}

void            ADelay::activate()
{
}

void            ADelay::dispatch_control()
{
  m_tempo = *p(peg_tempo);
  m_time_sw = *p(peg_time_sw);
  m_time_ms = *p(peg_time_ms);
  m_time_beat = *p(peg_time_beat);
  m_feedback = *p(peg_feedback);
  m_amount = *p(peg_amount);

  compute_rate();
}

void            ADelay::compute_rate()
{
  float tmp, tape_len_s;

  tape_len_s = (1.0 / m_sr) * m_tape_size;

  if (m_time_sw > 0.)
    {
      // compute rate from time_beat
      tmp = m_time_beat * (60. / m_tempo);
      m_rate = tape_len_s / tmp;
    }
  else
    {
      // compute rate from time_ms
      m_rate = tape_len_s / (m_time_sw / 1000);
    }
}

void            ADelay::run(uint32_t sample_count)
{
  unsigned int  i, j;
  float         *inL, *inR, *outL, *outR;
  float         tf, tmp;
  unsigned int  ti;

  dispatch_control();

  ti = (unsigned int) m_rate;

  // Feed tape
  for (i = sample_count - 1; i >= 0; i--)
    {
      for (j = 0; j < m_rate; j++)
        {
        }
    }

  // Output delay.
  for (i = 0; i < sample_count; i++)
    {
    }
}

/*
 * LV2Plugin stuffs
 */

void initialise() __attribute__((constructor));
void initialise()
{
  register_lv2_inst<ADelay>(peg_uri);
}
