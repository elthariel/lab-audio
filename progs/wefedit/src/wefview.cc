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

# define SAMPLE_PER_PIXEL 25

using namespace std;

WefView::WefView(Wef &a_wef)
  : m_wef(a_wef),
    m_zoom(1.0),
    m_clicked(false)
{
  set_size_request(m_wef.get_size() / (m_zoom * SAMPLE_PER_PIXEL), 250);
  set_events(get_events() | Gdk::SCROLL_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::BUTTON_PRESS_MASK);
}

void            WefView::set_zoom(float a_zoom)
{
  Gtk::Allocation allocation = get_allocation();
  const int h = allocation.get_height();

  m_zoom = a_zoom;
  set_size_request(m_wef.get_size() / (m_zoom * SAMPLE_PER_PIXEL), 250);
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
      double wef_offset = SAMPLE_PER_PIXEL * m_zoom;

      Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();

      if (event)
        {
          cr->rectangle(event->area.x, event->area.y,
                        event->area.width, event->area.height);
          cr->clip();
        }

      if (m_clicked)
        {
          cr->set_line_width(0);

          cr->set_source_rgba(1.0, 1.0, 1.0, 1.0);
          cr->rectangle(0.0, 0.0, m_start_pos, h);
          cr->stroke();
          cr->fill();

          cr->set_source_rgba(0.6, 0.6, 0.6, 1.0);
          cr->rectangle(m_start_pos, 0.0, m_end_pos, h);
          cr->stroke();
          cr->fill();

          cr->set_source_rgba(1.0, 1.0, 1.0, 1.0);
          cr->rectangle(m_end_pos, 0.0, w, h);
          cr->stroke();
          cr->fill();
        }
      else
        {
          cr->set_line_width(0);
          cr->set_source_rgba(1.0, 1.0, 1.0, 1.0);
          cr->rectangle(0.0, 0.0, w, h);
          cr->stroke();
        }

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

bool                    WefView::on_scroll_event(GdkEventScroll* event)
{
  if (event->direction == GDK_SCROLL_UP)
    {
      set_zoom(m_zoom * 0.75);
    }
  else
    {
      set_zoom(m_zoom * 1.25);
    }
  queue_draw();
  return true;
}

bool                    WefView::on_button_press_event(GdkEventButton* event)
{
  m_clicked = true;
  m_start_pos = m_end_pos = (unsigned int)event->x;
  queue_draw();
}

bool                    WefView::on_button_release_event(GdkEventButton* event)
{
  m_end_pos = (unsigned int) event->x;
  /*  if (m_end_pos > (m_start_pos - 2) && m_end_pos < (m_start_pos + 2))
      m_clicked = false;*/
  queue_draw();
}

