/*
** drumseqview.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Wed Apr 11 14:37:30 2007 Nahlwe
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
#include <stdio.h>
#include "drumseqview.hh"

using namespace std;

DrumSeqView::DrumSeqView(PatateGUI &a_gui,
                         unsigned int a_init_track)
  : m_gui(a_gui),
    m_track_id(a_init_track)
{
  unsigned int i;

  pack_start(m_seq_hbox);
  for (i = 0; i < 16; i++)
    {
      char label[32];
      sprintf(label, "%d", i);
      m_seq_hbox.pack_start(m_steps[i]);
      m_steps[i].set_label(label);
      m_steps[i].signal_clicked()
        .connect(sigc::bind<0>(sigc::mem_fun(*this,
                                             &DrumSeqView::step_pressed),
                               i));
    }
}

void                    DrumSeqView::step_pressed(unsigned int a_step_id)
{
  Event                 ev;

  ev.subsystem = Sys_DrumSeq;
  ev.type = Event::TypeNote;
  ev.data.note.chan = 1;
  if (m_steps[a_step_id].get_active())
    ev.data.note.note = a_step_id;
  else
    ev.data.note.note = a_step_id + 16;
  ev.data.note.vel = 50;

  if (m_gui.writer()->ready())
      m_gui.writer()->write(&ev);
}
