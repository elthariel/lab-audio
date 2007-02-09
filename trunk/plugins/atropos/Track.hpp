//
// Track.hpp for atropos in /home/elthariel/code/lab-audio/plugins/atropos
//
// Copyright 2007 BALLET Julien.
// Login   <elthariel@lse.epita.fr>
//
// Started on  Wed Feb  7 00:54:22 2007 Nahlwe
// Last update Thu Feb  8 05:56:46 2007 Nahlwe
//

#ifndef TRACK_HPP_
# define TRACK_HPP_

# include <vector>
# include "lv2instrument.hpp"
# include "lv2plugin.hpp"
# include "AnalogFilter.hpp"

class iTrack
{
public:
  iTrack(unsigned int sample_rate);
  iTrack(unsigned int sample_rate,
         iTrack *default_out,
         float default_out_amount);
  virtual ~iTrack();

  virtual void                  feed(float *in,
                                     unsigned int sample_count,
                                     float carried_amnt = 1.0);
  virtual int                   add_out(iTrack *track,
                                        float amount);
  virtual void                  set_amount(unsigned int track_id,
                                           float amount);
  virtual void                  set_track(unsigned int track_id,
                                          iTrack *new_out_track);
  virtual void                  set_mute(bool mute);
protected:
  iTrack();

  unsigned int                  m_sr;
  bool                          m_mute;
  std::vector<iTrack *>         m_out_tracks;
  std::vector<float>            m_out_amount;
};




class MixerTrack : public iTrack
{
public:
  //  MixerTrack(unsigned int sample_rate, unsigned int in_port);
  MixerTrack(unsigned int sample_rate,
             iTrack *default_out,
             float default_out_amount);

  virtual void                  feed(float *in,
                                     unsigned int sample_count,
                                     float carried_amnt = 1.0);
  void                          set_gain(unsigned char which,
                                         float gain);
  void                          set_crossover(unsigned char which,
                                              float freq);
  void                          set_in(float *in);
protected:
  float                         *m_in_port;

  AnalogFilter                  m_lp;
  AnalogFilter                  m_hp;

  float                         m_lp_gain;
  float                         m_bp_gain;
  float                         m_hp_gain;
  float                         m_lp_freq;
  float                         m_hp_freq;
};





class SendTrack : public iTrack
{
public:
  SendTrack(unsigned int sample_rate);
  SendTrack(unsigned int sample_rate,
            iTrack *default_out,
            float default_out_amount);

  virtual void                  feed(float *in,
                                     unsigned int sample_count,
                                     float carried_amnt = 1.0);
  virtual void                  feedback(unsigned int sample_count);
  void                          set_port(float *send, float *ret);
protected:
  float                         *m_send_port;
  float                         *m_ret_port;
};





class MasterTrack : public iTrack
{
public:
  MasterTrack(unsigned int sample_rate);

  virtual void                  feed(float *in,
                                     unsigned int sample_count,
                                     float carried_amnt = 1.0);
  virtual void                  set_out(float *out);
protected:
  float                         *m_out_port;
};

#endif
