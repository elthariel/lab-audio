//
// atropos.cpp for atropos in /home/elthariel/code/lab-audio/plugins/atropos
//
// Copyright 2007 BALLET Julien
// Login   <elthariel@lse.epita.fr>
//
// Started on  Wed Feb  7 09:03:52 2007 Nahlwe
// Last update Fri Feb  9 12:36:51 2007 Nahlwe
//

#include <iostream>
#include "atropos.peg"
#include "atropos.hpp"

using namespace std;

Atropos::Atropos(uint32_t rate, const char*,
                 const LV2_Host_Feature**)
  : LV2Plugin(peg_n_ports),
    m_sr(rate), m_pcount(peg_eq_crossover1_0 - peg_volume_0 + 1)
{
  unsigned int  i, j;

  // Create Master tracks
  m_master[0] = new MasterTrack(m_sr);
  m_master[1] = new MasterTrack(m_sr);

  // Create Send tracks
  for (i = 0; i < SEND_TRACK_COUNT; i++)
    {
      m_sends[i * 2] = new SendTrack(m_sr, m_master[0], 1.0);
      m_sends[i * 2 + 1] = new SendTrack(m_sr, m_master[1], 1.0);
    }

  // Create normal mixer tracks
  for (i = 0; i < STEREO_TRACK_COUNT * 2; i++)
    {
      m_mono[i] = new MixerTrack(m_sr, m_master[i % 2], 1.0);

      for (j = 0; j < SEND_TRACK_COUNT; j++)
        {
          m_mono[i]->add_out(m_sends[j * 2 + i % 2], 0.0);
        }
    }
}

void            Atropos::run(uint32_t sample_count)
{
  unsigned int  i;

  connect_audio();
  dispatch_ctrl_main();
  for (i = 0; i < STEREO_TRACK_COUNT * 2; i++)
    {
      dispatch_ctrl_track(i);
    }
  clean_outs(sample_count);
  process_audio(sample_count);
}

void          Atropos::connect_audio()
{
  unsigned int  i;

  m_master[0]->set_out(p(peg_main_out_l));
  m_master[1]->set_out(p(peg_main_out_r));

  for (i = 0; i < SEND_TRACK_COUNT * 2; i++)
    m_sends[i]->set_port(p(peg_send_0_l + i),
                         p(peg_send_0_ret_l + i));

  for (i = 0; i < STEREO_TRACK_COUNT * 2; i++)
    m_mono[i]->set_in(p(peg_track_0_l + i));
}

void    Atropos::clean_outs(uint32_t sample_count)
{
  unsigned int  i, j;
  float         *port;

  port = p(peg_main_out_l);
  for (i = 0; i < sample_count; i++)
    port[i] = 0.0;
  port = p(peg_main_out_r);
  for (i = 0; i < sample_count; i++)
    port[i] = 0.0;
  for (j = 0; j < SEND_TRACK_COUNT * 2; j++)
    {
      port = p(peg_send_0_l + j);
      for (i = 0; i < sample_count; i++)
        port[i] = 0.0;
    }
}

void    Atropos::process_audio(uint32_t sample_count)
{
  unsigned int  i;

  for (i = 0; i < STEREO_TRACK_COUNT * 2; i++)
    m_mono[i]->feed(0, sample_count);
  for (i = 0; i < SEND_TRACK_COUNT * 2; i++)
    m_sends[i]->feedback(sample_count);
}

void    Atropos::dispatch_ctrl_main()
{
  unsigned int  i;

  m_master[0]->set_amount(0, *p(peg_main_volume));
  m_master[1]->set_amount(0, *p(peg_main_volume));

  for (i = 0; i < SEND_TRACK_COUNT; i++)
    {
      m_sends[i * 2]->set_amount(0, *p(peg_send0_return + i));
      m_sends[i * 2 + 1]->set_amount(0, *p(peg_send0_return + i));
    }
}

void    Atropos::dispatch_ctrl_track(unsigned int stereo_track_id)
{
  unsigned int  i, j;

  for (i = 0; i < STEREO_TRACK_COUNT; i++)
    {
      // FIXME compute volume to reflect pan.
      m_mono[i * 2]->set_amount(0, *p(peg_volume_0 + i * 2));
      m_mono[i * 2 + 1]->set_amount(0, *p(peg_volume_0 + i * 2));
      for (j = 0; j < SEND_TRACK_COUNT; j++)
        {
          m_mono[i * 2]->set_amount(j + 1, *p(peg_send_fx0_0 + j));
          m_mono[i * 2 + 1]->set_amount(j + 1, *p(peg_send_fx0_0 + j));
        }
      for (j = 0; j < 3; j++)
        {
          //          m_mono[i * 2]->
        }
      // FIXME manage mute, solo, eqs params
    }
}


/*
 * LV2Plugin stuffs
 */

void initialise() __attribute__((constructor));
void initialise()
{
  register_lv2<Atropos>(peg_uri);
}
