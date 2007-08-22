/*
** event.cc
** Login : <elthariel@elthariel-desktop>
** Started on  Wed Aug 22 20:31:13 2007 Nahlwe
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
#include "event.hh"

void                  Event_new::inc_note(unsigned int offset)
{
  if ((note + offset) > 127)
    note = 127;
  else
    note += offset;
}

void                  Event_new::dec_note(unsigned int offset)
{
  if (note < offset)
    note = 0;
  else
    note -= offset;
}

void                  Event_new::inc_vel(unsigned int offset)
{
  if ((vel + offset) > 127)
    vel = 127;
  else
    vel += offset;
}

void                  Event_new::dec_vel(unsigned int offset)
{
  if (vel < offset)
    vel = 0;
  else
    vel -= offset;
}

void                  Event_new::inc_len(unsigned int offset)
{
  len += offset;
}

void                  Event_new::dec_len(unsigned int offset)
{
  if (len <= offset)
    len = 1;
  else
    len -= offset;
}
