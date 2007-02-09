//
// atropos.hpp for atropos in /home/elthariel/code/lab-audio/plugins/atropos
//
// Copyright 2007 BALLET Julien
// Login   <elthariel@lse.epita.fr>
//
// Started on  Wed Feb  7 09:02:49 2007 Nahlwe
// Last update Fri Feb  9 11:24:20 2007 Nahlwe
//

#ifndef ATROPOS_HPP_
# define ATROPOS_HPP_

# include "lv2plugin.hpp"
# include "atropos.peg"
# include "Track.hpp"

# define        SEND_TRACK_COUNT        4
# define        STEREO_TRACK_COUNT      16

class Atropos : public LV2Plugin
{
public:
  Atropos(uint32_t rate, const char*, const LV2_Host_Feature**);
  void          run(uint32_t sample_count);

protected:
  void          connect_audio();
  void          process_audio(uint32_t sample_count);
  void          clean_outs(uint32_t sample_count);
  void          dispatch_ctrl_main();
  void          dispatch_ctrl_track(unsigned int stereo_track_id);

  unsigned int  m_sr;
  unsigned int  m_pcount;

  MasterTrack   *m_master[2];
  SendTrack     *m_sends[SEND_TRACK_COUNT * 2];
  MixerTrack    *m_mono[STEREO_TRACK_COUNT * 2];
};

#endif
