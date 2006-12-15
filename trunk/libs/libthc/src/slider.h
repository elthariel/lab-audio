/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */


//
// Class: Slider
// Created by: GESTES Cedric <goctaf@gmail.com>
// Created on: Sun Dec  3 19:34:17 2006
//

#ifndef _SLIDER_H_
#define _SLIDER_H_
#include <gtkmm.h>
#include "widget.h"

namespace Thc {

class Slider : public Gtk::DrawingArea, public IWidget {
public:
  //Slider(Config& xmlconfig);
  Slider(float min = 0, float max = 10, float value = 0, bool integer = false, bool logarithmic = false, bool horizontal = true);
 
  //ICloWidget
  void on_mode_change();

protected:
  bool on_expose_event(GdkEventExpose* event);
  bool on_motion_notify_event(GdkEventMotion* event);
  bool on_button_press_event(GdkEventButton* event);
  bool on_scroll_event(GdkEventScroll* event);
  
//  int draw_digit(Cairo::RefPtr<Cairo::Context>& cc, char digit);
//  void draw_string(Cairo::RefPtr<Cairo::Context>& cc, const std::string& str,
//                   float x, float y);
  double map_to_adj(double knob);
  double map_to_knob(double adj);
  
  int m_click_offset;
  float m_value_offset;
  float m_red, m_green, m_blue;
  bool m_integer;
  bool m_logarithmic;
  bool m_horizontal;
  float m_step;
};


} //namespace Thc

#endif	//_SLIDER_H_
