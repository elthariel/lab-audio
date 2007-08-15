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

class RollView : public Gtk::DrawingArea
{
public:
  RollView(unsigned int a_note_h, unsigned int a_time_w,
           unsigned int a_times, unsigned int a_beats);
  virtual ~RollView();

protected:
  virtual bool          on_expose_event(GdkEventExpose *event);

  unsigned int          m_height, m_width, m_times, m_beats;
};


#endif	    /* !ROLL_VIEW_HH_ */
