/*
** transport.cc
** Login : <elthariel@elthariel-desktop>
** Started on  Wed Aug  1 22:13:28 2007 Nahlwe
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
#include "transport.hh"

using namespace std;

namespace Seq
{
  /*  template <>
      Transport     *TransportSingleton::m_instance = 0;*/

  Transport::Position::Position()
    : bars(0), beats(0), ticks(0)
  {
  }

  Transport::Position::Position(const Transport::Position &a_pos)
    : bars(a_pos.bars), beats(a_pos.beats), ticks(a_pos.ticks)
  {
  }

  Transport::Position::Position(unsigned int a_bars, unsigned int a_beats, unsigned int a_ticks)
    : bars(a_bars), beats(a_beats), ticks(a_ticks)
  {
  }

  Transport::Position::Position(uint64_t a_ticks)
  {
    unsigned int ppq = TimerSingleton::get().ppq();

    bars = a_ticks / (4 * ppq);
    a_ticks %= (4 * ppq);
    beats = a_ticks / ppq;
    ticks = a_ticks % ppq;
  }

  Transport::Position::operator uint64_t() const
  {
    unsigned int ppq = TimerSingleton::get().ppq();
    uint64_t res;

    res = ticks;
    res += beats * ppq;
    res += bars * 4 *ppq;

    return res;
  }

  Transport::Position   &Transport::Position::operator=(const Transport::Position &toadd)
  {
    bars = toadd.bars;

    ticks = toadd.ticks;

    beats = toadd.beats;
  }

  Transport::Position   &Transport::Position::operator+=(const Transport::Position &toadd)
  {
    unsigned int ppq = TimerSingleton::get().ppq();

    bars += toadd.bars;

    beats += toadd.beats;

    ticks += toadd.ticks;

    beats += ticks / ppq;
    ticks %= ppq;
    bars += beats / 4;
    beats %= 4;

    return *this;
  }

  Transport::Position          &Transport::Position::operator-=(const Transport::Position &pos)
  {
    unsigned int ppq = TimerSingleton::get().ppq();

    /// \todo Position::operator-=(const Position &pos)

    return *this;
  }

  Transport::Position          &Transport::Position::operator=(uint64_t toadd)
  {
    /// \todo Position::operator=(uint64_t)
  }

  Transport::Position          &Transport::Position::operator+=(uint64_t toadd)
  {
    /// \todo Position::operator+=(uint64_t)
  }

  bool              Transport::Position::zero() const
  {
    return (!bars) && (!beats) && (!ticks);
  }


  Transport::Transport()
    : m_state(Stopped), m_loop_end(1), m_last_tick(0)
  {
    TimerSingleton::get().samples_added().connect(sigc::mem_fun(*this, &Transport::run));
  }

  const Transport::Position                   &Transport::position() const
  {
    return m_current;
  }

  void                                        Transport::set_position(Position &a_pos)
  {
    m_current = a_pos;
  }

  void                                        Transport::forward(Transport::Position &a_pos)
  {
    m_current += a_pos;
  }

  void                                        Transport::backward(Transport::Position &a_pos)
  {
    m_current -= a_pos;
  }

  void                                        Transport::set_state(State a_state)
  {
    m_state = a_state;
  }

  Transport::State                            Transport::state() const
  {
    return m_state;
  }

  sigc::signal<void, Transport::Position &, Transport::Position &>  &Transport::signal_played()
  {
    return m_played;
  }

  void                                        Transport::run(uint64_t sample_count)
  {
    uint64_t ticks = TimerSingleton::get().ticks();

    //    cout << "Transport::run " << ticks << " " << m_state << " \t" << (ticks - m_last_tick) << endl;

    if (m_state == Running)
      {
        if (ticks > m_last_tick)
          {
            Position added(ticks - m_last_tick);
            m_played.emit(m_current, added);
            m_current += added;
          }
      }
    m_last_tick = ticks;
  }
}
