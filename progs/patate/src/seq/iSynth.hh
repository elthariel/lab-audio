/*
** iSynth.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Thu Apr 26 13:31:16 2007 Nahlwe
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

#ifndef   	ISYNTH_HH_
# define   	ISYNTH_HH_

#include <jack/jack.h>

namespace Seq
{
  class Note;

  class iSynth
  {
  public:
    virtual     ~iSynth(){}

    virtual void        play_note(const Seq::Note &a_note) = 0;
    virtual void        stop_note(const Seq::Note &a_note) = 0;
    virtual void        flush_note() = 0;
    virtual void        render(jack_nframes_t nframes,
                               jack_nframes_t sample_rate,
                               jack_default_audio_sample_t *outL,
                               jack_default_audio_sample_t *outR) = 0;
  protected:
  };

  class iSynthContainer
  {
  public:
    virtual ~iSynthContainer(){}
    virtual iSynth      *synth(unsigned int i) = 0;
  };
};

# include "part.hh"

#endif	    /* !ISYNTH_HH_ */
