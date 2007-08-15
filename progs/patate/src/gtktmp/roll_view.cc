/*
** roll_view.cc
** Login : <elthariel@elthariel-desktop>
** Started on  Wed Aug 15 19:14:51 2007 Nahlwe
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
#include "roll_view.hh"

RollView::  RollView(unsigned int a_note_h, unsigned int a_time_w,
                     unsigned int a_times, unsigned int a_beats)
  : m_height(a_note_h), m_width(a_time_w),
    m_times(a_times), m_beats(a_beats)
{
  set_size_request(-1, a_note_h * 120);
}

RollView::~RollView()
{
}

bool                    RollView::on_expose_event(GdkEventExpose *event)
{
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

      cr->set_source_rgb(0.0, 0.0, 0.1);
      cr->paint();
      cr->set_source_rgba(1.0, 1.0, 1.0, 0.8);
      for (i = 0; i < notes; i++)
        {
          if (i % 12 == 0)
            cr->set_line_width(1.5);
          else
            cr->set_line_width(0.9);

          cr->move_to(0.0, height - i * m_height);
          cr->line_to(width, height - i * m_height);
          cr->stroke();
        }

      for (i = 0; (i * m_width) < width; i ++)
        {
          if (i % (m_times * m_beats) == 0)
            {
              cr->set_line_width(1.5);
              cr->set_source_rgb(1.0, 1.0, 1.0);
            }
          else if (i % m_times == 0)
            {
              cr->set_line_width(1.0);
              cr->set_source_rgb(0.9, 0.9, 0.9);
            }
          else
            {
              cr->set_line_width(0.5);
              cr->set_source_rgb(0.6, 0.6, 0.6);
            }

          cr->move_to(i * m_width, 0.0);
          cr->line_to(i * m_width, height);
          cr->stroke();
        }
    }
}



