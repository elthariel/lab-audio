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

using namespace std;

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
      unsigned int wef_w = m_wef.get_size();
      double wef_offset =((double) wef_w) / ((double)w);

      Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();

      if (event)
        {
          cr->rectangle(event->area.x, event->area.y,
                        event->area.width, event->area.height);
          cr->clip();
        }

      cr->set_line_width(0);
      cr->set_source_rgba(1.0, 1.0, 1.0, 1.0);
      cr->rectangle(0.0, 0.0, w, h);
      cr->stroke();

      cr->set_line_width(1);
      cr->set_source_rgba(0.4, 0.4, 0.4, 1.0);
      cr->move_to(0.0, h / 2.0);
      cr->line_to(w, h / 2.0);
      cr->stroke();

      cr->set_source_rgba(0.0, 0.0, 0.3, 1.0);
      cr->set_line_width(1.2);
      cr->move_to(0.0, h / 2.0);
      for (unsigned int i = 0; i < w; i++)
        cr->line_to(i, (m_wef[((unsigned int)i * wef_offset)] + 1.0) * 0.5 * h);
      cr->stroke();
    }
}


