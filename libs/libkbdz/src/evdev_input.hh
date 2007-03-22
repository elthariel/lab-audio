/*
** evdev_input.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Thu Mar 22 12:30:00 2007 Nahlwe
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

#ifndef   	EVDEV_INPUT_HH_
# define   	EVDEV_INPUT_HH_

#include <linux/input.h>
#include "iInput.hh"
#include "kevent.hh"
#include <string>

class EvdevInput : public iInput<kEvent>
{
public:
  EvdevInput(Semaphore &a_sem, std::string a_path);
  ~EvdevInput();

private:
  virtual void          thread_fun();
  void                  open_dev();
  bool                  read_event(input_event *a_ev);
  bool                  evdev_to_kevent(kEvent *a_kev,
                                        input_event *a_ev);
  void                  send_kevent(kEvent *a_kev);

  int                   m_fd;
  std::string           m_path;
  bool                  active;
};

#endif	    /* !EVDEV_INPUT_HH_ */
