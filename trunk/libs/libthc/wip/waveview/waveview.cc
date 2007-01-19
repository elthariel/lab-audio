/*
** WaveView.cc
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

#include <iostream>
#include "waveview.h"

WaveView::WaveView()
  :data(0), data_size(0), channels(0)
{
}

bool                    WaveView::on_expose_event(GdkEventExpose* event)
{
  Cairo::RefPtr<Cairo::Context>         cc;
  unsigned int                          mono_frames;

  //  if(!m_cc)
  cc = this->get_window()->create_cairo_context();

  if (event)
    {
      // clip to the area indicated by the expose event so that we only redraw
      // the portion of the window that needs to be redrawn
      cc->rectangle(event->area.x, event->area.y,
                    event->area.width, event->area.height);
      cc->clip();
    }

  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();

  mono_frames = data_size / channels;
  float w_ratio = ((float) mono_frames) / width;

  cc->set_line_width(1.0);
   cc->set_line_cap(Cairo::LINE_CAP_ROUND);
  //LINE_CAP_ROUND
  //LINE_CAP_SQUARE
  cc->set_source_rgb(1.0, 0.0, 0.0);

  cc->move_to(0, (height / 2) * (data[0] + 1.0));
  unsigned int offset_y, offset_y2, j; //start bound, last bound
  float avg;
  for (int i = 1; i < width; i++)
    {
      offset_y = (unsigned int)(i * w_ratio);
      offset_y2 = (unsigned int)((i + 1) * w_ratio);
      for (j = offset_y; j < offset_y2; j++)
        avg += data[j];
      avg /= offset_y2 - offset_y; //FIXME peut etre bug off-by-one fealarach
      cc->line_to(i, (height / 2) * (avg + 1.0));
    }
  cc->stroke();
  /*
  cc->line_to(200,200);
  cc->stroke();*/

  return (true);
}

void                    WaveView::set_data(sample_t *d, unsigned int size,
                                         unsigned char chan)
{
  data = d;
  data_size = size;
  channels = chan;
}
