/*
** Sequence.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Tue Jun 26 23:29:42 2007 Nahlwe
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

#ifndef   	SEQUENCE_HH_
# define   	SEQUENCE_HH_

#include "event_bus.hh"
#include "timer.hh"
#include <map>

namespace Seq
{

  /*!
  ** \brief Represents a sequence of (musical) event.
  ** Implemented using multimap (red-black tree) assuring logarithmic worst
  ** time complexity (if no duplicate keys).
  **
  ** Should be used with a real-time safe allocator.
  ** FIXME : use a real-time safe allocator.
  */
  template <class T>
  class Sequence
  {
  public:
    typedef std::multimap<tick, T*>             _sequence;
    typedef typename _sequence::iterator        iterator;
    typedef typename _sequence::const_iterator  const_iterator;
    typedef typename _sequence::value_type      value_type;

    Sequence(short a_res = 1, unsigned short a_seq_len = 1,
             EventBus<T> *a_bus = 0);
    void                                connect(EventBus<T> *a_bus = 0);

    void                                play(tick a_pos, tick a_len);

    void                                add(tick a_pos, T &);
    void                                remove(tick a_pos);
    void                                remove_range(tick low_bound, tick high_bound);

    void                                clear();

    short                               get_res();
    void                                set_res(short a_new_res);
    unsigned short                      get_len();
    void                                set_len(unsigned short a_new_len);
  protected:
    _sequence                           m_seq; /// Actual container for event sequence.

    /// Out EventBus (it is responsible to give the event to the right module) @see EventBus
    EventBus<T>                         *m_out;

    unsigned short                      m_seq_len; /// Sequence len (in bars)
    short                               m_res; /// Resolution of the pattern ( > 0 => x ppq; < 0 ==> / pqq)
  };



  /*!
  ** \brief StepSequence(Adapter), this class adapts a Sequence into a step sequence.
  **
  */
  /*  template <class T>
  class StepSequence
  {
    typedef unsigned short              step;
  public:
    StepSequence(Sequence<T> &);
    void                                add(step a_pos, T &a_event);
    void                                remove(step a_pos);
    void                                remove_range(step a_low_bound, step a_high_bound);
    void                                clear();

  protected:
    Sequence<T>                         &m_seq;
    };*/

};

#include "Sequence.cc"

#endif	    /* !SEQUENCE_HH_ */

