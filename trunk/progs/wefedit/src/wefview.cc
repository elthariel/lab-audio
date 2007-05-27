/*
** wefview.cc
** Login : <elthariel@elthariel-desktop>
** Started on  Sun May 27 14:50:33 2007 Nahlwe
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
#include "wefview.hh"
#include <cmath>

WefView::WefView(Wef &a_wef)
  : m_wef(a_wef)
{

}

bool            WefView::on_expose_event(GdkEventExpose* event)
{
  Glib::RefPtr<Gdk::Window> window = get_window();
  if(window)
    {
      Gtk::Allocation allocation = get_allocation();
      const int w = allocation.get_width();
      const int h = allocation.get_height();
      float i;
      unsigned int wef_w = m_wef.get_size();
      double wef_offset =((double) wef_w) / w;

      Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();

      if (event)
        {
          cr->rectangle(event->area.x, event->area.y,
                        event->area.width, event->area.height);
          cr->clip();
        }

      cr->move_to(0.0, h / 2.0);
      for (i = 0.0; i < w; i += wef_offset)
        cr->line_to(i, (m_wef[(unsigned int)i] + 1.0) * 0.5 * h);
      cr->stroke();
    }
}


