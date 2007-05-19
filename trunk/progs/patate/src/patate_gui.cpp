/*
** patate_gui.cpp
** Login : <elthariel@elthariel-desktop>
** Started on  Tue Apr 10 02:57:27 2007 Nahlwe
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
#include "patate_gui.hh"

using namespace std;

PatateGUI::PatateGUI(LFRingBufferReader<Event> *a_reader,
                     LFRingBufferWriter<Event> *a_writer,
                     Patate &a_patate)
  : m_reader(a_reader),
    m_writer(a_writer),
    m_patate(a_patate)
{
  unsigned int i;

  add(m_main_vbox);
  for (i = 0; i < 16; i++)
    {
      m_seqview[i] = new DrumSeqView(*this, i);
      m_main_vbox.pack_end(*m_seqview[i]);
    }
  show_all();
}

PatateGUI::~PatateGUI()
{
}

void            PatateGUI::gui_update()
{
  Event         ev;

  if (m_reader->ready())
    {
      m_reader->read(&ev);
      process_gui_event(ev);
    }
}

void            PatateGUI::process_gui_event(Event &a_ev)
{
}

LFRingBufferReader<Event>     *PatateGUI::reader()
{
  return m_reader;
}

LFRingBufferWriter<Event>     *PatateGUI::writer()
{
  return m_writer;
}
