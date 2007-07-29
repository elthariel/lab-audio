/*
** timer.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Thu Apr 26 10:37:09 2007 Nahlwe
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

#ifndef   	TIMER_HH_
# define   	TIMER_HH_

#include <time.h>

namespace Seq
{

  class Timer
  {
  public:
    Timer(unsigned int a_bpm, unsigned int a_ppq);
    void                  set_ppq(unsigned int a_ppq);
    void                  set_bpm(unsigned int a_bpm);
    void                  start();
    void                  pause();
    void                  stop();
    bool                  paused();
    bool                  started();
    unsigned int          ticks(unsigned int frames);
    uint64_t              frames();
  protected:
    void                  update_tick_len();
    void                  update_ticks();

    unsigned int          m_bpm;
    unsigned int          m_ppq;

    bool                  m_started;
    bool                  m_paused;
    uint64_t              m_frames;
    unsigned int          m_remaining_frames;
  };

};

#endif	    /* !TIMER_HH_ */
