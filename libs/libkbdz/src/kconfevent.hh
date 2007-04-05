/*
** kconfevent.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Thu Mar 22 14:31:27 2007 Nahlwe
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

#ifndef   	KCONFEVENT_HH_
# define   	KCONFEVENT_HH_

#include <sigc++/sigc++.h>
#include "iInput.hh"
#include "kevent.hh"
#include <string>

struct kConfAddEventInput
{
  iInput<kEvent>        *input;
};

struct kConfRemoveEventInput
{
  iInput<kEvent>        *input;
};

struct kConfDeferredExec
{
  sigc::signal0<void>   *fun;
};

struct kConf
{
  enum kConfType
    {
      AddEventInput,
      RemoveEventInput,
      DeferredExec,
      TypeCount
    }                           type;
  union
  {
    kConfAddEventInput          add_ev_input;
    kConfRemoveEventInput       rem_ev_input;
    kConfDeferredExec           deferred_exec;
  }                             data;
};

#endif	    /* !KCONFEVENT_HH_ */
