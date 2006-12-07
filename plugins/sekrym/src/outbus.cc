/*
** outbus.cc
** Login : <elthariel@localhost.localdomain>
** Started on  Thu Dec  7 03:53:34 2006 Elthariel
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

#include <iostream>
#include "outbus.hh"

OutBus::OutBus()
{
}

OutBus::OutBus(LV2Plugin &a_plugin, uint32_t a_port)
  :m_plugin(a_plugin), m_outport(a_port)
{
}



void            OutBus::push_timestamp(LV2_MIDI *a_midi_port)
{
  *((double *)(a_midi_port->data + a_midi_port->size)) =
    m_plugin.get_current_sample();
  a_midi_port->size += sizeof(double);
}

void            OutBus::push_char(LV2_MIDI *a_midi_port, unsigned char c)
{
  a_midi_port->data[a_midi_port->size] = c;
  a_midi_port->size++;
}

void            OutBus::new_frame()
{
  LV2_MIDI*     midi_port;

  midi_port = m_plugin.p<LV2_MIDI>(m_outport);

  midi_port->event_count = 0;
  midi_port->size = 0;
}



void            OutBus::send_note_on(unsigned char a_note, unsigned char a_vel)
{
  unsigned char[4] data = {3, 0x90, a_note, a_vel};
  LV2_MIDI      *port = m_plugin.p<LV2_MIDI>(m_outport);

  if (port->capacity > sizeof(double) + 4)
    {
      push_timestamp(port);
      for (int i = 0; i < 4; i++)
        push_char(port, data[i]);
      port->event_count++;
    }
}

void            OutBus::send_note_off(unsigned char a_note, unsigned char a_vel)
{
  unsigned char[4] data = {3, 0x80, a_note, a_vel};
  LV2_MIDI      *port = m_plugin.p<LV2_MIDI>(m_outport);

  if (port->capacity > sizeof(double) + 4)
    {
      push_timestamp(port);
      for (int i = 0; i < 4; i++)
        push_char(port, data[i]);
      port->event_count++;
    }
}
