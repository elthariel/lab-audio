//
// atropos.cpp for atropos in /home/elthariel/code/lab-audio/plugins/atropos
//
// Copyright 2007 BALLET Julien
// Login   <elthariel@lse.epita.fr>
//
// Started on  Wed Feb  7 09:03:52 2007 Nahlwe
// Last update Thu Feb 15 06:07:21 2007 Nahlwe
//

#include <iostream>
#include "cigue.peg"
#include "cigue.hpp"
#include "lv2-midifunctions.h"
#include <cmath>

using namespace std;

Cigue::Cigue(uint32_t rate, const char*,
             const LV2_Host_Feature**)
  : LV2Instrument(peg_n_ports), m_sr(rate),
    m_aalias(rate, 0, rate / 2, 0., 2),
    m_filter(rate, 0, 20000., 5., 1),
    m_filter2(rate, 2, 20000., 5., 1),
    m_saw("/home/elthariel/code/lab-audio/progs/basewef/wefs/saw.wef"),
    m_square("/home/elthariel/code/lab-audio/progs/basewef/wefs/square.wef"),
    m_exp("/home/elthariel/code/lab-audio/progs/basewef/wefs/exp.wef"),
    m_wave (true),
    m_pos(0.), m_cur_rate(0.), m_target_rate(0.),
    m_note_count(0), m_glide_on(false),
    m_note(-1), m_note_len(0.),
    m_cutoff(2.5), m_res(0.), m_env_mod(0.),
    m_env_decay(0.5), m_glide(200.), m_dist(0.)
{
}

# define LOG_10 2.302585093
# define ARG2FREQ(ff) 2 * exp((ff) * LOG_10)

void            Cigue::activate()
{
  unsigned int size, i;
  float a;
  /*
  size = m_saw.get_size();
  cout << "Saw wavetable length" << size << endl;
  for (i = 0; i < size; i++)
  cout << i << " " << m_saw[i] << endl;*/
  /*  for (a = 1; a <= 4; a += 0.1)
      {
      cout << ARG2FREQ(a) << endl;
      }*/
}

void            Cigue::process_midi(unsigned int sample_count)
{
  LV2_MIDIState         midi = {p<LV2_MIDI>(peg_midi), sample_count, 0};
  double                event_time;
  uint32_t              event_size;
  unsigned char         *ev;
  uint32_t              when = 0;
  unsigned int          size = m_saw.get_size();

  when = uint32_t(lv2midi_get_event(&midi, &event_time, &event_size, &ev));
  while (event_size)
    {
      switch(ev[0])
        {
        case 0x90:
          m_note = ev[1];
          m_vel = ev[2];
          if (m_note_count == 0)
            {
              m_note_len = 0.;
              m_cur_rate = ((float)size) / m_sr;
              m_cur_rate *= m_freqs[m_note];
              m_cur_rate += m_pitch;
            }
          else
            {
              float     rate_diff, tmp2;
              // Glide part 1
              m_target_rate = ((float)size) / m_sr;
              m_target_rate *= m_freqs[m_note];
              m_target_rate += m_pitch;
              rate_diff = m_target_rate - m_cur_rate;
              m_rate_inc = rate_diff / ((m_glide / 1000.) * m_sr);
              m_glide_on = true;
            }
          m_note_count++;
          break;
        case 0x80:
          if (m_note_count == 1)
            {
              m_note = -1;
              m_glide_on = false;
            }
          if (m_note_count > 0)
            m_note_count--;
          break;
        }
      lv2midi_step(&midi);
      when = uint32_t(lv2midi_get_event(&midi, &event_time,
                                        &event_size, &ev));
    }
}

void            Cigue::dispatch_control()
{
  m_pitch = *p(peg_pitch);
  m_cutoff = *p(peg_cutoff);
  m_res = *p(peg_res);
  m_env_mod = *p(peg_env_mod);
  m_env_decay = *p(peg_env_decay);
  m_glide = *p(peg_glide);
  m_dist = *p(peg_dist);
}

void            Cigue::run(uint32_t sample_count)
{
  unsigned int  i;
  unsigned int  size = m_saw.get_size();;
  float         *out = p(peg_main_out);
  float         offset = 0;
  float         frac;
  unsigned int  ipos;
  float         env;

  process_midi(sample_count);
  dispatch_control();

  // Env pos
  env = m_exp.get_size() / (m_env_decay * m_sr);
  env = m_note_len * env;

  if (m_note >= 0)
    {
      // VCO
      offset += m_pitch;
      for (i = 0; i < sample_count; i++)
        {
          ipos = (unsigned int) m_pos;
          frac = m_pos - ipos;
          if (m_wave)
            out[i] = (1.0 - frac) * m_saw[ipos] + (frac) * m_saw[ipos + 1];
          else
            out[i] = (1.0 - frac) * m_square[ipos] + (frac) * m_square[ipos + 1];
          m_pos += m_cur_rate;
          // Glide part 2
          if (m_glide_on)
            m_cur_rate += m_rate_inc;
          if (m_cur_rate >= m_target_rate)
            {
              m_cur_rate = m_target_rate;
              m_glide_on = false;
            }
          while (m_pos >= size)
            m_pos -= size;
        }
      m_aalias.filterout(out, sample_count);

      // VCF
      if (env > m_exp.get_size())
        {
          m_filter.setfreq_and_q(ARG2FREQ(m_cutoff),
                                 m_res);
         m_filter2.setfreq_and_q(ARG2FREQ(m_cutoff),
                                 m_res);
        }
      else
        {
          m_filter.setfreq_and_q(ARG2FREQ(m_cutoff
                                          + m_exp[env] * m_env_mod *
                                          (((float) m_vel) / 127)),
                                 m_res);
          m_filter2.setfreq_and_q(ARG2FREQ(m_cutoff
                                           + m_exp[env] * m_env_mod *
                                           (((float) m_vel) / 127)),
                                  m_res);
        }
      m_filter.filterout(out, sample_count);
      m_filter2.filterout(out, sample_count);
      m_note_len += sample_count;

      // Distortion
      for (i = 0; i < sample_count; i++)
        out[i] = (1.0 - m_dist) * out[i] + m_dist * tanhf(out[i]);
    }
  else
    for(i = 0; i < sample_count; i++)
      out[i] =0.;
}

/*
 * LV2Plugin stuffs
 */

void initialise() __attribute__((constructor));
void initialise()
{
  register_lv2_inst<Cigue>(peg_uri);
}
