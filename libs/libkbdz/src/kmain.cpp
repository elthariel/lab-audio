/*
** kinputregistry.cpp
** Login : <elthariel@lse.epita.fr>
** Started on  Fri Jan 26 06:52:51 2007 Nahlwe
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

#include <pthread.h>
#include "kmain.hh"

kMain::kMain()
{
}

kMain::~kMain()
{
  // FIXME Kill all input
}

Semaphore               &kMain::get_sem()
{
  return m_sem;
}

void                    kMain::register_event_input(iInput<kEvent> &a_input)
{
  m_ev_inputs.push_back(&a_input);
  m_ev_readers.push_back(a_input.get_reader());
}

void                    kMain::unregister_event_input(iInput<kEvent> &a_input)
{
  // FIXME Unregister event.
}

bool                    kMain::read_event(kEvent *a_ev)
{
  std::list<LFRingBufferReader<kEvent> *>::iterator iter;
  bool found = false;

  for (iter = m_ev_readers.begin();
       iter != m_ev_readers.end() && !found;
       iter++)
    if ((*iter)->ready())
      {
        found = true;
        (*iter)->read(a_ev);
      }
  return found;
}

void                    kMain::main_loop()
{
  bool terminated = false;

  while(!terminated)
    {
    }
}

