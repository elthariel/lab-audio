/*
** kinputregistry.hh
** Login : <elthariel@elthariel-desktop>
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

#ifndef   	KMAIN_HH_
# define   	KMAIN_HH_

#include <vector>
#include <list>
#include "foncteurs.hpp"
#include "thread.hpp"
#include "smp_uint.hh"
#include "iInput.hh"
#include "kconfevent.hh"
#include "kevent.hh"
#include "mapping.hh"

class kMain : public iFoncteur0<void>
{
public:
  kMain(LFRingBufferReader<kConf> *a_base_conf_input);
  ~kMain();

  Semaphore             &get_sem();
  Thread                &run();

private:
  virtual void          operator()();
  void                  main_loop();
  void                  register_event_input(iInput<kEvent> &);
  void                  unregister_event_input(iInput<kEvent> &);
  void                  register_conf_input(LFRingBufferReader<kConf> *);
  void                  unregister_conf_input(LFRingBufferReader<kConf> *);
  void                  set_map(iMapping *a_map);
  bool                  read_event(kEvent *);
  void                  process_event(kEvent &);
  bool                  read_conf(kConf *);
  void                  process_conf(kConf &);

  std::list<iInput<kEvent> *>                   m_ev_inputs;
  std::list<LFRingBufferReader<kEvent> *>       m_ev_readers;
  std::list<LFRingBufferReader<kConf> *>        m_conf_readers;
  Semaphore                                     m_sem;
  Thread                                        *m_thread;
  iMapping                                      *m_map;
};

#endif	    /* !KMAIN_HH_ */
