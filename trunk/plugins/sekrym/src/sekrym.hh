/*
** sekrym.hh
** Login : <elthariel@localhost.localdomain>
** Started on  Sun Dec  3 09:55:06 2006 Elthariel
** $Id$
**
** Copyright (C) 2006 Elthariel
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

#ifndef   	SEKRYM_HH_
# define   	SEKRYM_HH_

#include <vector>
#include "lv2plugin.hpp"
#include "outbus.hh"
#include "pattern.hh"

# define        SEKRYM_DEFAULT_TEMPO    180
# define        SEKRYM_PPQ              96
# define        SEKRYM_PAT_COUNT        32

class Sekrym : public LV2Plugin
{
protected:
  OutBus                m_outbus;
  Pattern               m_free_pattern;
  vector<Pattern>       m_pat;
  bool                  m_playing;

  // remaining samples since the last tick.
  unsigned int          m_sample_rate;
  float                 m_remaining_samples;
  uint64_t              m_ticks;
  unsigned char         m_current_pattern;
  double                m_current_sample;

  unsigned int          m_bpm;
  unsigned int          m_tick_res; // Pulse per quarter.
  float                 m_tick_len; // len of a tick in sample

public:

  Sekrym(unsigned long sample_rate,
         const char* bundle_path,
         const LV2_Host_Feature** features);
  virtual ~Sekrym();

  virtual void          run(uint32_t sample_count);

  /** This reset the playaing state of sekrym.
   */
  void                  reset();

  /** Play() Causes the current pattern to be played.
   */
  void                  play();
  /** stopm stops the play.
   */
  void                  stop();

  /** Resets the playing state & clear the pattern bank.
   */
  void                  clear();

  /** Set the current bpm.
   */
  void                  set_bpm(uint32_t a_bpm = 0);

  double                get_current_sample();
};

#endif	    /* !SEKRYM_HH_ */
