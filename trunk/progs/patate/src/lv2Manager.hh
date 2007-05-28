/*
** lv2Manager.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Sun May 20 19:48:49 2007 Nahlwe
** $Id$
**
** Copyright (C) 2007 Nahlwe
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#ifndef   	LV2MANAGER_HH_
# define   	LV2MANAGER_HH_

#include <slv2/slv2.h>
#include "seq/iSynth.hh"
#include "patate.hh"
#include "lv2-midifunctions.h"

#define LV2_MIDI_BUFFER_SIZE 1024

extern const LV2_Host_Feature **g_features;

bool                            lv2_is_synth(SLV2Plugin a_plug);

class Lv2Adapter : public Seq::iSynth
{
public:
  Lv2Adapter(SLV2Plugin a_plugin,
             unsigned int a_sample_rate);
  virtual ~Lv2Adapter();

  virtual void        play_note(const Seq::Note &a_note);
  virtual void        stop_note(const Seq::Note &a_note);
  virtual void        cc(unsigned int control, float value);
  virtual void        flush_note();
  virtual void        render(jack_nframes_t nframes,
                             jack_nframes_t sample_rate,
                             unsigned int chan_count,
                             jack_default_audio_sample_t **out);
protected:
  void                  create_ports();
  void                  connect_ports();
  void                  frame(jack_nframes_t nframes);

  LV2_Host_Feature      **m_feat;
  SLV2Plugin            m_plugin;
  SLV2Instance          m_lv2;
  unsigned int          m_port_count;
  float                 *m_controls;
  LV2_MIDI              m_midi_port;
  bool                  m_midi_connected;
  int                   m_audio_ports_index[2];
  LV2_MIDIState         m_midi_state;
};

class Lv2Manager
{
public:
  Lv2Manager(Patate &a_patate);

  Lv2Adapter                    *make_lv2(unsigned int a_id);
protected:
  void                          init_slv2();

  SLV2World                     m_world;
  SLV2Plugins                   m_plugins;
  Patate                        &m_patate;
};


#endif	    /* !LV2MANAGER_HH_ */
