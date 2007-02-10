//
// atropos.cpp for atropos in /home/elthariel/code/lab-audio/plugins/atropos
//
// Copyright 2007 BALLET Julien
// Login   <elthariel@lse.epita.fr>
//
// Started on  Wed Feb  7 09:03:52 2007 Nahlwe
// Last update Sat Feb 10 11:39:37 2007 Nahlwe
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
    m_aalias(rate, 0, 22000., 0., 4),
    m_filter(rate, 2, 4000., 5.0, 4),
    m_saw("/home/elthariel/code/lab-audio/progs/basewef/wefs/saw.wef"),
    m_exp("/home/elthariel/code/lab-audio/progs/basewef/wefs/exp.wef"),
    m_pos(0), m_note(-1), m_cutoff(500.),
    m_note_len(0.)
{
}

void            Cigue::activate()
{
  unsigned int size, i;
  /*
  size = m_saw.get_size();
  cout << "Saw wavetable length" << size << endl;
  for (i = 0; i < size; i++)
  cout << i << " " << m_saw[i] << endl;*/
}

void            Cigue::process_midi(unsigned int sample_count)
{
  LV2_MIDIState         midi = {p<LV2_MIDI>(peg_midi), sample_count, 0};
  double                event_time;
  uint32_t              event_size;
  unsigned char         *ev;
  uint32_t              when = 0;

  when = uint32_t(lv2midi_get_event(&midi, &event_time, &event_size, &ev));
  while (event_size)
    {
      cout << "midi event received " << ev[0] << endl;
      switch(ev[0])
        {
        case 0x90:
          m_note = ev[1];
          m_vel = ev[2];
          m_pos = 0.0;
          cout << "note_on " << endl;
          break;
        case 0x80:
          m_note = -1;
          m_note_len = 0.;
          cout << "note_off " << endl;
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
}

void            Cigue::run(uint32_t sample_count)
{
  unsigned int  i;
  unsigned int  size = m_saw.get_size();;
  float         *out = p(peg_main_out);
  float         offset = 0;
  float         env;

  process_midi(sample_count);
  dispatch_control();

  if (m_note >= 0)
    {
      // VCO
      offset = ((float)size) / m_sr;
      offset *= m_freqs[m_note];
      offset += m_pitch;
      for (i = 0; i < sample_count; i++)
        {
          out[i] = m_saw[(unsigned int)m_pos];
          m_pos += offset;
          while (m_pos >= size)
            m_pos -= size;
        }
      m_aalias.filterout(out, sample_count);

      // VCF
      float tmp = m_exp.get_size() / m_sr;
      env = (1.0 / m_env_decay) / tmp; //pos in env
      tmp = m_exp.get_size() / (m_env_decay * m_sr);
      tmp = m_note_len * tmp;
      cout << tmp << endl;
      if (tmp > m_exp.get_size())
        m_filter.setfreq_and_q(m_cutoff,
                               m_res);
      else
        m_filter.setfreq_and_q(m_cutoff + m_exp[tmp] * m_env_mod,
                               m_res);
      m_filter.filterout(out, sample_count);
      m_note_len += sample_count;
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
