/*
** kevent.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Thu Jan 25 07:03:24 2007 Nahlwe
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

/* Please note that kevent mean kbdz event, and not
 * kernel event
 */

#ifndef   	KEVENT_HH_
# define   	KEVENT_HH_

enum kEvent
  {
    kNote,
    kCtrlAbs,
    kCtrlRel,
    kTimestamp
  };

struct kEventNote
{
  char note;
  char vel;
};

struct kEventCtrlAbs
{
  uint32_t      control;
  uint32_t      value;
};

struct kEventCtrlRel
{
  uint32_t      control;
  int32_t       value;
};

struct kEvent
{
  uint32_t      device;
  uint32_t      type;
  union
  {
    kEventNote          note;
    kEventCtrlAbs       abs;
    kEventCtrlRel       rel;
  };
};

#endif	    /* !KEVENT_HH_ */
