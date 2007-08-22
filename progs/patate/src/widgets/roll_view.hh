/*
** roll_view.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Wed Aug 15 19:09:31 2007 Nahlwe
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

#ifndef   	ROLL_VIEW_HH_
# define   	ROLL_VIEW_HH_

#include <gtkmm/drawingarea.h>
#include "../seq/part.hh"
#include "../seq/Sequence.hh"
#include "timer.hh"
#include "event.hh"

/// \todo use signature
class RollView : public Gtk::DrawingArea
{
public:
  RollView(unsigned int a_note_h, unsigned int a_time_w,
           unsigned int a_times, unsigned int a_beats,
           Seq::Sequence<Event_new> *a_seq = 0);
  virtual ~RollView();

  void                  display_note(Cairo::RefPtr<Cairo::Context> cr,
                                     Seq::tick pos_x, char note, unsigned int len,
                                     char vel, bool a_current); /// Draw a single note
  /// Display the note sequence and the note being edited.
  void                  display_sequence(Cairo::RefPtr<Cairo::Context> cr);
  void                  draw_background(Cairo::RefPtr<Cairo::Context> cr); /// draw the note grid.

protected:
  virtual bool          on_expose_event(GdkEventExpose *event);
  virtual bool          on_key_press_event(GdkEventKey *event);

  unsigned int          m_height, m_width, m_times, m_beats;
  Seq::Sequence<Event_new> *m_seq;
  Event_new             *m_floatting_note; /// The note being moved.
  Seq::tick             m_current; /// The position of the note being moved.
};


#endif	    /* !ROLL_VIEW_HH_ */

