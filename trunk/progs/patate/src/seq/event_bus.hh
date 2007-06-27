es/*
** event_bus.hh
** Login : <lta@elthariel-main>
** Started on  Wed Jun 27 02:49:33 2007 Elthariel
** $Id$
**
** Copyright (C) 2007 Elthariel
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

#ifndef   	EVENT_BUS_HH_
# define   	EVENT_BUS_HH_

#include <vector>
#include "iSynth.hh"

namespace Seq
{
  /*!
  ** \brief EventBus is an event "stream" class which links sequencers parts
  ** to actual synths & Fx.
  ** The event buss will probably allow in the future the use of lv2 midi/event fx.
  ** It is also responsible for sending note off associated to each note_on/len couple
  ** a sequencer part pass to itself.
  */
  template <class T>
  class EventBus
  {
  public:
    EventBus();
    void                        send(T &a_ev);
    void                        connect(iSynth *a_synth);
  protected:
    iSynth                      *m_synth;
  };


  /*!
  ** \brief Bus Container & Manager
  **
  */
  template <class T>
  class MasterEventBus
  {
    typedef EventBus<T>         Bus;
    typedef std::vector<Bus *>  BusVector;
  public:
    MasterEventBus(unsigned short a_bus_count);
    unsigned short              size();
    void                        set_size(unsigned short a_new_size);
    Bus                         *operator[](unsigned short);
  protected:
    BusVector                   m_buses;
  };

};
#endif	    /* !EVENT_BUS_HH_ */
