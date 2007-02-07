//
// Track.cpp for atropos in /home/elthariel/code/lab-audio/plugins/atropos
//
// Copyright 2007 BALLET Julien
// Login   <elthariel@lse.epita.fr>
//
// Started on  Wed Feb  7 00:55:41 2007 Nahlwe
// Last update Wed Feb  7 09:38:33 2007 Nahlwe
//

#include <iostream>
#include "Track.hpp"

/*
 * iTrack class implementation
 */

iTrack::iTrack(){}
iTrack::~iTrack(){}

iTrack::iTrack(unsigned int sample_rate)
  : m_sr(sample_rate)
{
}

iTrack::iTrack(unsigned int sample_rate,
               iTrack *default_out, float default_out_amount)
  : m_sr(sample_rate)
{
  m_out_tracks[0] = default_out;
  m_out_amount[0] = default_out_amount;
}

void                    iTrack::feed(float *in,
                                     unsigned int sample_count,
                                     float carried_amnt)
{
  unsigned int i;

  for (i = 0; i < m_out_tracks.size(); i++)
    {
      m_out_tracks[i]->feed(in, sample_count,
                            carried_amnt * m_out_amount[i]);
    }
}

int                     iTrack::add_out(iTrack *track,
                                        float amount)
{
  if (track)
    {
      m_out_tracks.push_back(track);
      m_out_amount.push_back(amount);
      return (m_out_tracks.size() - 1);
    }
  else
    return (-1);
}

void                    iTrack::set_amount(unsigned int track_id,
                                           float amount)
{
  if (track_id < m_out_tracks.size())
    m_out_amount[track_id] = amount;
}

void                    iTrack::set_track(unsigned int track_id,
                                          iTrack *new_out_track)
{
  if (track_id < m_out_tracks.size())
    m_out_tracks[track_id] = new_out_track;
}

void                    iTrack::set_mute(bool mute)
{
  m_mute = mute;
}

/*
 * MonoTrack class
 */

MixerTrack::MixerTrack(unsigned int sample_rate,
                       iTrack *default_out,
                       float default_out_amount,
                       unsigned int in_port)
  : iTrack(sample_rate, default_out, default_out_amount),
    m_in_port(in_port),
    m_lp(sample_rate, 0, 400, 0.0, 2),
    m_hp(sample_rate, 1, 4000, 0.0, 2),
    m_lp_gain(1.0), m_bp_gain(1.0), m_hp_gain(1.0),
    m_lp_freq(400.0), m_hp_freq(4000.0)
{
}

// this is an input then *in is unused
void            MixerTrack::feed(float *in,
                                 unsigned int sample_count,
                                 float carried_amnt)
{
  in = p(m_in_port);
  float         *in_iter;
  float         tmp[3];

  // FIXME manage post/pre volume sends.
  iTrack::feed(in, sample_count, 1.0);
}

void            MixerTrack::set_gain(unsigned char which,
                                     float gain)
{
  switch (which)
    {
    case 0:
      m_lp_gain = gain;
      break;
    case 1:
      m_bp_gain = gain;
      break;
    case 2:
      m_hp_gain = gain;
      break;
    }
}

void            MixerTrack::set_crossover(unsigned char which,
                                          float freq)
{
  switch (which)
    {
    case 0:
      if (m_lp_freq != freq)
        {
          m_lp_freq = freq;
          m_lp.setfreq(freq);
        }
      break;
    case 1:
      if (m_hp_freq != freq)
        {
          m_hp_freq = freq;
          m_hp.setfreq(freq);
        }
      break;
    }
}




/*
 * SendTrack class
 */
SendTrack::SendTrack(unsigned int sample_rate,
                     unsigned int send_port,
                     unsigned int ret_port)
  : iTrack(sample_rate),
    m_send_port(send_port),
    m_ret_port(ret_port)
{
}

SendTrack::SendTrack(unsigned int sample_rate,
                     iTrack *default_out,
                     float default_out_amount,
                     unsigned int send_port,
                     unsigned int ret_port)
  : iTrack(sample_rate, default_out, default_out_amount),
    m_send_port(send_port),
    m_ret_port(ret_port)
{
}

// FIXME find a way to avoid sample_count latency increase.
void                    SendTrack::feed(float *in,
                                      unsigned int sample_count,
                                      float carried_amnt)
{
  float                 send_in, send_out;
  unsigned int          i;

  send_in = p(m_ret_port);
  send_out = p(m_send_port);

  for (i = 0; i < sample_count; i++)
    {
      send_out[i] += in[i] * carried_amnt;
    }
  iTrack::feed(send_in, sample_count);
}




/*
 * MasterTrack class
 */
MasterTrack::MasterTrack(unsigned int sample_rate,
                         unsigned int out_port)
  : iTrack(sample_rate, 0, 1.0),
    m_out_port(out_port)
{
}

void            MasterTrack::feed(float *in,
                                  unsigned int sample_count,
                                  float carried_amnt)
{
  float         *out;
  unsigned int  i;

  out = p(m_out_port);
  for (i = 0; i < sample_count; i++)
    out[i] += carried_amnt * in[i] * m_out_amount[0];
}
