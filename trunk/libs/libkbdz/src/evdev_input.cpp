/*
** evdev_input.cpp
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

#include <iostream>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "evdev_input.hh"

using namespace std;

EvdevInput::EvdevInput(Semaphore &a_sem, std::string a_path)
  : iInput<kEvent>(a_sem, 100),
    m_path(a_path),
    active(true)
{
}

EvdevInput::~EvdevInput()
{
  close(m_fd);
}


//EvdevInput::EvdevInput(){}

void                    EvdevInput::thread_fun()
{
  kEvent                kev;
  input_event           ev;

  open_dev();
  while (active)
    {
      if (read_event(&ev))
        {
          if (evdev_to_kevent(&kev, &ev))
            send_kevent(&kev);
        }
    }
  cerr << "Evdev (" << m_path << ") thread exited." << endl;
}

void                    EvdevInput::open_dev()
{
  if ((m_fd = open(m_path.c_str(), O_RDONLY)) == -1)
    {
      cerr << "Unable to opne evdev (" << m_path << ") : "
           << strerror(errno) << endl;
      active = false;
      // FIXME throw an exception.
    }
}

bool                    EvdevInput::read_event(input_event *a_ev)
{
  int                   res;

  res = read(m_fd, (void *)a_ev, sizeof(input_event));
  if (res < 0)
    {
      cerr << "An error occur while reading (" << m_path
           << ") : " << strerror(errno) << endl;
      active = false;
      return false;
    }
  else if (res != sizeof(input_event))
    {
      cerr << "Unable to read full event (" << m_path
           << ")." << endl;
      return false;
    }
  else
    return true;

}

bool                    EvdevInput::evdev_to_kevent(kEvent *a_kev,
                                                    input_event *a_ev)
{


  a_kev->device = 0;
  switch(a_ev->type)
    {
    case EV_KEY:
      a_kev->type = kEvent::kNote;
      a_kev->data.note.note = a_ev->code;
      a_kev->data.note.vel = a_ev->value;
      return true;
      break;

    case EV_REL:
      a_kev->type = kEvent::kCtrlRel;
      a_kev->data.rel.control = a_ev->code;
      a_kev->data.rel.value = a_ev->value;
      return true;
      break;

    case EV_ABS:
      a_kev->type = kEvent::kCtrlAbs;
      a_kev->data.abs.control = a_ev->code;
      a_kev->data.abs.value = a_ev->value;
      return true;
      break;

    default:
      return false;
    }
}

void                    EvdevInput::send_kevent(kEvent *a_kev)
{
  if (m_writer->ready())
    m_writer->write(a_kev);
}
