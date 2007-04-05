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
#include <iostream>
#include "kmain.hh"

using namespace std;

kMain::kMain(LFRingBufferReader<kConf> *a_base_conf_input)
{
  m_conf_readers.push_back(a_base_conf_input);
}

kMain::~kMain()
{
  // FIXME Kill all input
}

void                    kMain::operator()()
{
  main_loop();
}

Thread                  &kMain::run()
{
  m_thread = new Thread(*this);
  return *m_thread;
}

Semaphore               &kMain::get_sem()
{
  return m_sem;
}

void                    kMain::register_event_input(iInput<kEvent> &a_input)
{
  m_ev_inputs.push_back(&a_input);
  m_ev_readers.push_back(a_input.get_reader());
  cerr << "Registered input" << endl;
}

void                    kMain::unregister_event_input(iInput<kEvent> &a_input)
{
  // FIXME Unregister event input.
}

void            kMain::register_conf_input(LFRingBufferReader<kConf> *a_input)
{
  m_conf_readers.push_back(a_input);
}

void            kMain::unregister_conf_input(LFRingBufferReader<kConf> *a_input)
{
  // FIXME Unregister conf input.
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

void                    kMain::process_event(kEvent &a_ev)
{
  cout << "received an event" << endl;
}


bool                    kMain::read_conf(kConf *a_conf_ev)
{
  std::list<LFRingBufferReader<kConf> *>::iterator iter;
  bool found = false;

  for (iter = m_conf_readers.begin();
       iter != m_conf_readers.end() && !found;
       iter++)
    if ((*iter)->ready())
      {
        found = true;
        (*iter)->read(a_conf_ev);
      }
  return found;
}

void                    kMain::process_conf(kConf &a_conf_ev)
{
  cerr << "Received a conf event" << endl;

  switch(a_conf_ev.type)
    {
    case kConf::AddEventInput:
      register_event_input(*a_conf_ev.data.add_ev_input.input);
      break;
    case kConf::RemoveEventInput:
      unregister_event_input(*a_conf_ev.data.rem_ev_input.input);
      break;
    default:
      break;
    }
}

void                    kMain::main_loop()
{
  kConf                 conf_ev;
  kEvent                ev;
  bool terminated = false;

  cerr << "Entering kmain loop" << endl;

  while(!terminated)
    {
      --m_sem;
      if(read_conf(&conf_ev))
        process_conf(conf_ev);
      else if (read_event(&ev))
        process_event(ev);
    }
  cerr << "Exiting kmain loop" << endl;
}
