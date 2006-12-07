/*
** outbus.hh
** Login : <elthariel@localhost.localdomain>
** Started on  Sat Dec  2 03:54:13 2006 Elthariel
** $Id$
**
** Copyright (C) 2006 Elthariel
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

#ifndef   	OUTBUS_HH_
# define   	OUTBUS_HH_

#include "lv2plugin.hh"
#include "lv2-miditype.h"

class OutBus
{
private:
  OutBus();

  LV2Plugin     &m_plugin;
  uint32_t      m_outport;

  void          push_timestamp();
  void          push_char(unsigned char c);

public:
  OutBus(LV2Plugin &a_plugin, uint32_t a_port);

  void          new_frame();

  void          send_note_on(unsigned char a_note, unsigned char a_vel);
  void          send_note_off(unsigned char a_note, unsigned char a_vel);
};

#endif	    /* !OUTBUS_HH_ */
