//
// atropos.cpp for atropos in /home/elthariel/code/lab-audio/plugins/atropos
//
// Copyright 2007 BALLET Julien
// Login   <elthariel@lse.epita.fr>
//
// Started on  Wed Feb  7 09:03:52 2007 Nahlwe
// Last update Wed Feb  7 10:08:17 2007 Nahlwe
//

#include <iostream>
#include "atropos.peg"
#include "atropos.hpp"

using namespace std;

Atropos::Atropos(uint32_t rate, const char*,
                 const LV2_Host_Feature**)
  : LV2Instrument(peg_n_ports),
    m_sr(rate), m_pcount(peg_eq_crossover1_0 - peg_volume_0 + 1)
{
  unsigned int  i, j;

  // Create Master tracks
  m_master[0] = new MasterTrack(m_sr, peg_main_out_l);
  m_master[1] = new MasterTrack(m_sr, peg_main_out_r);

  // Create Send tracks
  for (i = 0; i < SEND_TRACK_COUNT; i++)
    {
      m_sends[i * 2] = new SendTrack(m_sr, m_master[0], 1.0,
                                     peg_send_0_l + i * 2,
                                     peg_send_0_ret_l + i * 2);
      m_sends[i * 2 + 1] = new SendTrack(m_sr, m_master[1], 1.0,
                                         peg_send_0_r + i * 2,
                                         peg_send_0_ret_r + i * 2);
    }

  // Create normal mixer tracks
  for (i = 0; i < STEREO_TRACK_COUNT * 2; i++)
    {
      m_mono[i] = new MixerTrack(m_sr, m_master[i % 2], 1.0,
                                 peg_track_0_l + i);

      for (j = 0; j < SEND_TRACK_COUNT; j++)
        {
          m_mono[i]->add_out(m_sends[j * 2 + i % 2], 0.0);
        }
    }
}

void            Atropos::run(uint32_t sample_count)
{
  unsigned int  i;

  dispatch_ctrl_main();
  for (i = 0; i < STEREO_TRACK_COUNT * 2; i++)
    dispatch_ctrl_track(i);
  process_audio();
}

void    Atropos::process_audio()
{
}

void    Atropos::dispatch_ctrl_main()
{
}

void    Atropos::dispatch_ctrl_track(unsigned int stereo_track_id)
{
}
