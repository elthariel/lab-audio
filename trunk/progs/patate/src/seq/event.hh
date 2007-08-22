/*
** gui_event.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Tue Apr 10 03:29:04 2007 Nahlwe
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

#ifndef   	EVENT_HH_
# define   	EVENT_HH_

struct EventNote
{
  char                  chan;
  char                  note;
  char                  vel;
  bool                  on;
};

struct EventCtrl
{
  char                  chan;
  char                  ctrl;
  char                  val;
};

enum SubSystem
  {
    Sys_Main,
    Sys_Part,
    Sys_Play,
    Sys_Gui
  };

struct Event_old
{
  SubSystem             subsystem;
  enum EventType
    {
      TypeNote,
      TypeCtrl,
      TypeSysEx,
      TypeCount
    }                   type;
  union
  {
    EventNote           note;
    EventCtrl           ctrl;
  }                     data;
};

typedef Event_old Event;

struct Event_new
{
  Event_new():note(0), vel(0), len(0) {}
  Event_new(Event_new &e):note(e.note), vel(e.vel), len(e.len) {}
  unsigned char         note;
  unsigned char         vel;
  uint16_t              pad0;
  uint32_t              len;

  void                  inc_note(unsigned int offset = 1);
  void                  dec_note(unsigned int offset = 1);
  void                  inc_vel(unsigned int offset = 1);
  void                  dec_vel(unsigned int offset = 1);
  void                  inc_len(unsigned int offset = 1);
  void                  dec_len(unsigned int offset = 1);
};

#endif	    /* !GUI_EVENT_HH_ */
