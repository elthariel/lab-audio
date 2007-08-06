/*
** part.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Thu Apr 26 12:50:29 2007 Nahlwe
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

#ifndef   	PART_HH_
# define   	PART_HH_

# include <list>
# include "timer.hh"
# include "event.hh"
# include "event_bus.hh"
# include "Sequence.hh"

namespace Seq
{
# define NOTE_PARAMS    4

  struct Note
  {
    Note();
    char                note;
    char                vel;
    unsigned int        start;
    unsigned int        len;
    unsigned int        rem;
    float               param[NOTE_PARAMS];
  };

  /*!
  ** \brief represent a part in a pattern.
  ** \todo support different resolution.
  */

  class Part
  {
  public:
    Part(unsigned int a_part_index,
         unsigned int a_seq_len = 1, int a_res = 1);
    ~Part();

    void                        play(tick a_pos, tick a_tick);
    void                        flush();
    void                        add_note(Event a_ev,
                                         tick position);
    bool                        rem_note(tick a_begin = 0,
                                         tick a_end = 0);
    void                        add_step(Note &a_note,
                                         unsigned int a_bar,
                                         unsigned int a_step);
    void                        rem_step(unsigned int a_bar,
                                         unsigned int a_step);

    void                        set_mres(int a_res = 1);
    void                        connect(EventBus<Event> &a_event_bus);

  protected:

    Sequence<Event>     m_note_sequence;
    Sequence<Event>     m_cc_sequence;
    unsigned int        m_part_index;
    unsigned int        m_seq_len;
    int                 m_res;
  };

  typedef SingletonInitialized<EventBusContainer<Event> >        MasterEventBus;

};

#endif	    /* !PART_HH_ */
