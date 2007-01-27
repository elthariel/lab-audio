/*
** WaveView.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Tue Jan 16 03:15:27 2007 Nahlwe
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

#ifndef   	WAVIEW_HH_
# define   	WAVIEW_HH_

#include <gtkmm.h>
#include <thcwidget.h>

class WaveView : public ThcWidget<Gtk::DrawingArea>
{
public:
  WaveView();

  typedef float                 sample_t;
  virtual bool                  on_expose_event(GdkEventExpose* event);
  //  void                          render_data(sample_t *, unsigned int);
  void                          set_data(sample_t *, unsigned int, unsigned char);
  void                          remove_data();

private:
  sample_t                      *data;
  unsigned int                  data_size;
  unsigned char                 channels;

};

/*
void            set_sample_window(int size);
void            set_scroll_ref(double percent_of_window);
void            set_scroll_pos_abs(double pos_in_sample);
void            set_scroll_pos_rel(double pos_in_percent);
void            set_scroll_pos_offset(double offset in sample);

void            load_raw();
void            load_stripe();
 */

#endif	    /* !WAVIEW_HH_ */
