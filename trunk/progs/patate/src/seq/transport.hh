/*
** transport.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Wed Aug  1 22:13:19 2007 Nahlwe
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

#ifndef   	TRANSPORT_HH_
# define   	TRANSPORT_HH_

#include "timer.hh"

namespace Seq
{
  class Transport
  {
    enum State
      {
        Started,
        Paused,
        Stopped
      };
    struct Position
    {
      Position();
      unsigned int      bars;
      unsigned int      beats;
      unsigned int      ticks;
    };
  public:
    Transport(Timer &s_seq);
    unsigned int        bars() const;
    unsigned int        beats() const;
    unsigned int        ticks() const;
    const Position      &position() const;
    uint64_t            ticks_total() const;
    void                next_bar();
    void                prev_bar();
    void                start();
    void                stop();
    void                pause();
    State               state();
  protected:

    // interface to the 'user' things.
    Timer               &m_timer;
    State               m_state;
    Position            m_current;
    Position            m_loop_start;
    Position            m_loop_end;

    // interface to the timer.

  };
};

#endif	    /* !TRANSPORT_HH_ */
