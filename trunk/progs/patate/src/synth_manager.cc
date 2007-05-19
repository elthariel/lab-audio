/*
** synth_manager.cc
** Login : <elthariel@elthariel-desktop>
** Started on  Fri May 18 00:54:34 2007 Nahlwe
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

#include <iostream>
#include "synth_manager.hh"

SynthManager::SynthManager(unsigned int size)
  : m_synths(size, 0)
{
}

SynthManager::~SynthManager()
{
}

unsigned int          SynthManager::get_synth_count()
{
  return m_synths.size();
}

Seq::iSynth           *SynthManager::synth(unsigned int i)
{
  return m_synths[i];
}

void                  SynthManager::synth(unsigned int i,
                                          Seq::iSynth &a_synth)
{
  m_synths[i] = &a_synth;
}








/*
 * DspSynthAdapter
 */
DspSynthAdapter::DspSynthAdapter(Dsp::iSynth &synth)
  : m_synth(synth)
{
}

void        DspSynthAdapter::play_note(const Seq::Note &a_note)
{
  m_synth.note_on(a_note.note, a_note.vel);
  //FIXME
}

void        DspSynthAdapter::stop_note(const Seq::Note &a_note)
{
  m_synth.note_off(a_note.note, a_note.vel);
  //FIXME
}

void        DspSynthAdapter::flush_note()
{
  m_synth.reset();
}

void        DspSynthAdapter::render(jack_nframes_t nframes,
                                    jack_nframes_t sample_rate,
                                    unsigned int chan_count,
                                    jack_default_audio_sample_t **out)
{
  m_synth.render(nframes, sample_rate,
                 chan_count, out);
}
