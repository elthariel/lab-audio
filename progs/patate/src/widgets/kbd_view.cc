/*
** kbd_view.cc
** Login : <elthariel@elthariel-desktop>
** Started on  Wed Aug 15 00:44:34 2007 Nahlwe
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
#include "kbd_view.hh"

KbdView::KbdView(unsigned int a_note_h, unsigned int a_note_w)
  : m_height(a_note_h), m_width(a_note_w)
{
  set_size_request(m_width, m_height * 120);
}

KbdView::~KbdView()
{
}

bool            KbdView::on_expose_event(GdkEventExpose* event)
{
  static bool   blacks[12] = {false, true, false, true, false,
                                false, true, false, true, false, true, false};
  unsigned int  notes, i;

  Glib::RefPtr<Gdk::Window> window = get_window();

  if(window)
    {
      Gtk::Allocation allocation = get_allocation();
      const int width = allocation.get_width();
      const int height = allocation.get_height();

      Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();

      if (event)
        {
          cr->rectangle(event->area.x, event->area.y,
                        event->area.width, event->area.height);
          cr->clip();
        }

      notes = 10 * 12;

      cr->move_to(0.0, 0.0);

      cr->set_line_width(1.0);
      for (i = 0; i < notes; i++)
        {
          cr->begin_new_path();
          cr->rectangle(0.0, height - (i + 1) * m_height,
                        m_width, m_height);
          if (blacks[i % 12])
            cr->set_source_rgb(0.0, 0.0, 0.0);
          else
            cr->set_source_rgb(1.0, 1.0, 1.0);
          cr->fill_preserve();
          cr->set_source_rgb(0.0, 0.0, 0.0);
          cr->stroke();
        }
    }

}


