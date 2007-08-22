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
#include <gdk/gdkkeysyms.h>
#include <gdk/gdktypes.h>
#include "roll_view.hh"

using namespace std;

RollView::  RollView(unsigned int a_note_h, unsigned int a_time_w,
                     unsigned int a_times, unsigned int a_beats,
                     Seq::Sequence<Event_new> *a_seq)
  : m_height(a_note_h), m_width(a_time_w),
    m_times(a_times), m_beats(a_beats),
    m_seq(a_seq), m_floatting_note(0), m_current(0)
{
  property_can_focus().set_value(true);
  grab_focus();
  add_events(Gdk::KEY_PRESS_MASK);
  set_size_request(-1, a_note_h * 120);
}

RollView::~RollView()
{
}

bool                    RollView::on_expose_event(GdkEventExpose *event)
{
  Glib::RefPtr<Gdk::Window> window = get_window();

  if(window)
    {
      Gtk::Allocation allocation = get_allocation();
      const int width = allocation.get_width();
      const int height = allocation.get_height();

      Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();
      //      cr->set_antialias(Cairo::ANTIALIAS_NONE);
      //      cr->set_antialias(Cairo::ANTIALIAS_SUBPIXEL);

      if (event)
        {
          cr->rectangle(event->area.x, event->area.y,
                        event->area.width, event->area.height);
          cr->clip();
        }

      draw_background(cr);
      display_sequence(cr);
    }
}

/// \todo use caching to avoid redrawing from scratch each time.
void                  RollView::draw_background(Cairo::RefPtr<Cairo::Context> cr)
{
  unsigned int  notes, i;

  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();

  notes = 10 * 12;

  cr->set_source_rgb(0.0, 0.0, 0.1);
  cr->paint();
  cr->set_source_rgba(1.0, 1.0, 1.0, 0.8);
  for (i = 0; i < notes; i++)
    {
      if (i % 12 == 0)
        cr->set_line_width(1.3);
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
          cr->set_source_rgba(1.0, 1.0, 1.0, 0.4);
        }
      else if (i % m_times == 0)
        {
          cr->set_line_width(1.0);
          cr->set_source_rgba(0.9, 0.9, 0.9, 0.5);
        }
      else
        {
          cr->set_line_width(0.5);
          cr->set_source_rgba(0.6, 0.6, 0.6, 0.7);
        }

      cr->move_to(i * m_width, 0.0);
      cr->line_to(i * m_width, height);
      cr->stroke();
    }
}

void                  RollView::display_note(Cairo::RefPtr<Cairo::Context> cr,
                                             Seq::tick pos_x, char note, unsigned int len,
                                             char vel, bool a_current)
{
  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();
  unsigned char lw = 2;
  float ftick_len, flen, fpos_x;

  ftick_len = (float)m_width / (float) Seq::TimerSingleton::get().ppq();
  flen = len * ftick_len;
  fpos_x = pos_x * ftick_len;

  cr->save();
  cr->begin_new_path();

  cr->set_line_width(lw * 2);

  cr->set_source_rgb(1.0 - vel / 127.0, 1.0 - vel / 127.0, 1.0 - vel / 127.0);
  cr->rectangle(fpos_x, height - (note + 1) * m_height,
                flen, m_height);
  cr->fill();

  if (a_current)
    {
      cr->set_source_rgb(0.8, 1.0, 0.8);
      cr->stroke();
    }

//   // bottom line
//   cr->set_source_rgba(p0 / 127.0, 0.0, 0.0, 0.8);
//   cr->move_to(pos_x, height - note * m_height - lw);
//   cr->line_to(pos_x + len - lw, height - note * m_height - lw);
//   cr->stroke();

//   // right line
//   cr->set_source_rgba(0.0, p1 / 127.0, 0.0, 0.8);
//   cr->move_to(pos_x + len - lw, height - note * m_height);
//   cr->line_to(pos_x + len - lw, height - (note + 1) * m_height);
//   cr->stroke();

//   // top line
//   cr->set_source_rgba(0.0, 0.0, p2 / 127.0, 0.8);
//   cr->move_to(pos_x + len - 2 * lw, height - (note + 1) * m_height + lw);
//   cr->line_to(pos_x, height - (note + 1) * m_height + lw);
//   cr->stroke();

  cr->restore();
}

bool                    RollView::on_key_press_event(GdkEventKey *event)
{
  Seq::Sequence<Event_new>::iterator i;
  unsigned int ppq = Seq::TimerSingleton::get().ppq();

  bool                  redraw = false;
  if (!m_floatting_note)
    {
      m_floatting_note = new Event_new;
      m_floatting_note->len = ppq * 4;
      m_floatting_note->vel = 65;
      m_current = 0;
      m_seq->add(m_current, *m_floatting_note);
    }

  switch (event->keyval)
    {
    case GDK_Up:
      if (event->state & GDK_CONTROL_MASK)
        m_floatting_note->inc_len(ppq);
      else
        m_floatting_note->inc_note();
      redraw = true;
      break;
    case GDK_Down:
      if (event->state & GDK_CONTROL_MASK)
        m_floatting_note->dec_len(ppq);
      else
        m_floatting_note->dec_note();
      redraw = true;
      break;
    case GDK_Left:
      if (event->state & GDK_CONTROL_MASK)
        m_floatting_note->dec_len();
      else
        {
          if (m_current < ppq)
            {
          m_seq->move(m_current, *m_floatting_note, 0);
          m_current = 0;
            }
          else
            {
              m_seq->move(m_current, *m_floatting_note,  m_current - ppq);
              m_current -= ppq;
            }
        }
      redraw = true;
      break;
    case GDK_Right:
      if (event->state & GDK_CONTROL_MASK)
        m_floatting_note->dec_len();
      else
        m_seq->move(m_current, *m_floatting_note, m_current + ppq);
      m_current += ppq;
      redraw = true;
      break;
    case GDK_Return:
      m_floatting_note = new Event_new(*m_floatting_note);
      m_seq->add(m_current + m_floatting_note->len, *m_floatting_note);
      m_current = m_current + m_floatting_note->len;
      redraw = true;
      break;
    };

  if (redraw)
    {
      queue_draw();
      return true;
    }
  else
    return false;
}

void                    RollView::display_sequence(Cairo::RefPtr<Cairo::Context> cr)
{
  if (m_seq)
    {
      Seq::Sequence<Event_new>::iterator iter;

      for(iter = m_seq->begin(); iter != m_seq->end(); iter++)
        {
          if((*iter).first == m_current)
            display_note(cr, (*iter).first, (*iter).second->note, (*iter).second->len,
                         (*iter).second->vel, true);
          else
            display_note(cr, (*iter).first, (*iter).second->note, (*iter).second->len,
                         (*iter).second->vel, true);
        }
    }
}


