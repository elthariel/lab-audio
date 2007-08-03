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

#include "../generic/singleton.hh"
#include <sigc++/sigc++.h>
#include "timer.hh"

namespace Seq
{
  class Transport
  {
    enum State
      {
        Running,
        Paused,
        Stopped
      };
    struct Position
    {
      Position();
      Position(uint64_t);
      Position(unsigned int a_bars, unsigned int a_beats, unsigned int a_ticks = 0);
      Position(const Position &);
      operator uint64_t() const;
      Position          &operator=(const Position &);
      Position          &operator+=(const Position &);
      Position          &operator-=(const Position &);
      Position          &operator=(uint64_t);
      Position          &operator+=(uint64_t);
      bool              zero() const;

      unsigned int      bars;
      unsigned int      beats;
      unsigned int      ticks;
    };

  public:
    Transport();
    const Position                              &position() const;
    void                                        set_position(Position &a_pos);
    void                                        forward(Position &);
    void                                        backward(Position &);
    void                                        set_state(State);
    State                                       state() const;
    sigc::signal<void, Position &, Position &>  &signal_played();
    void                                        run();

  protected:
    // interface to the 'user' things.
    State                                       m_state;
    Position                                    m_current;
    Position                                    m_loop_start;
    Position                                    m_loop_end;
    sigc::signal<void, Position &, Position &>  m_played;

    // interface to the timer things.
    uint64_t                                    m_last_tick;
  };

  typedef Singleton<Transport>                  TransportSingleton;

};

#endif	    /* !TRANSPORT_HH_ */
