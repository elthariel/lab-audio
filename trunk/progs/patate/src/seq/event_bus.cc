/*
** event_bus.cc
** Login : <lta@elthariel-main>
** Started on  Wed Jun 27 03:51:22 2007 Elthariel
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

#include <iostream>
#include "event_bus.hh"


/*
 * EventBus class
 */
template <class T>
EventBus<T>::EventBus()
  : m_synth(0)
{
}

template <class T>
void                        EventBus<T>::send(T &a_ev)
{
  // FIXME send event
}

template <class T>
void                        EventBus<T>::connect(iSynth *a_synth)
{
  m_synth = a_synth;
}










/*
 * MasterEventBus class
 */

template <class T>
MasterEventBus<T>::MasterEventBus(unsigned short a_bus_count)
  : m_buses(a_bus_count, 0)
{
}

template <class T>
unsigned short                MasterEventBus<T>::size()
{
  return m_buses.size();
}

template <class T>
void                          MasterEventBus<T>::set_size(unsigned short a_new_size)
{
  m_buses.resize(a_new_size);
}

template <class T>
Bus                           *MasterEventBus<T>::operator[](unsigned short a_index)
{
  if (a_index >= m_buses.size())
    return 0;
  else
    return m_buses[a_index];
}



