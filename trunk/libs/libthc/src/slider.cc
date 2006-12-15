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
//
// Created by: GESTES Cedric <goctaf@gmail.com>
// Created on: Sun Dec  3 19:34:17 2006
//

#include <iostream>
#include <string>
#include <cairomm/cairomm.h>

#include "include/slider.h"


namespace Thc {

using namespace std;

Slider::Slider(float min, float max, float value, bool integer, bool logarithmic, bool horizontal)
  : m_integer(integer),
    m_logarithmic(logarithmic),
    m_step(0),
    m_horizontal(horizontal) {
  m_supported_mode = ModeNormal & ModeConnect;
  m_params.push_back(Gtk::Adjustment(min, min, max));
  set_size_request(64, 32);
  add_events(Gdk::EXPOSURE_MASK | Gdk::BUTTON1_MOTION_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::SCROLL_MASK);
  m_params[0].signal_value_changed().connect(mem_fun(*this, &Slider::queue_draw));
  if (m_integer)
    m_step = 1.0 / (max - min);
  else
    m_step = 1.0 / 30;
  m_params[0].set_value(value);
}

void Slider::on_mode_change() {
  queue_draw();
}

bool Slider::on_expose_event(GdkEventExpose* event) {
  
  Glib::RefPtr<Gdk::Window> win = get_window();
  Glib::RefPtr<Gdk::GC> gc = Gdk::GC::create(win);
  Cairo::RefPtr<Cairo::Context> cc = win->create_cairo_context();
  float value;

  cc->set_line_join(Cairo::LINE_JOIN_ROUND);
  cc->set_source_rgba(127, 127, 127, 0.3);
  if (m_mode == ModeNormal) {
  	cc->move_to(2, 5);
  	cc->line_to(37, 5);
  	value = m_params[0].get_value();
  	if (m_integer)
    	value = floor(value + 0.5);
  	value = (value - m_params[0].get_lower()) * 36 / (m_params[0].get_upper() - m_params[0].get_lower());
  	cc->move_to((int)value + 2, 2);
  	cc->line_to((int)value + 2, 8);
  } else if (m_mode == ModeConnect) {
  	cc->move_to(0, 0);
  	cc->line_to(40, 10);
  	cc->move_to(40, 0);
  	cc->line_to(0, 10);
  }
	
  cc->set_source_rgb(0, 0, 0);
  cc->stroke();
  return true;
}


bool Slider::on_motion_notify_event(GdkEventMotion* event) {
  float scale = 200;
  float value;
  
  if (event->state & GDK_SHIFT_MASK)
    scale *= 200;
  value = m_value_offset + ((m_click_offset - event->y) / scale);
  value = value < 0 ? 0 : value;
  value = value > 1 ? 1 : value;
  m_params[0].set_value(map_to_adj(value));
  return true;
}


bool Slider::on_button_press_event(GdkEventButton* event) {
  m_click_offset = (int)event->y;
  m_value_offset = map_to_knob(m_params[0].get_value());
  return true;
}


bool Slider::on_scroll_event(GdkEventScroll* event) {
  double step = m_step;
  if (event->state & GDK_SHIFT_MASK && !m_integer)
    step *= 0.01;
  if (event->direction == GDK_SCROLL_UP)
    m_params[0].set_value(map_to_adj(map_to_knob(m_params[0].get_value()) + step));
  else if (event->direction == GDK_SCROLL_DOWN)
    m_params[0].set_value(map_to_adj(map_to_knob(m_params[0].get_value()) - step));
  return true;
}

/*
int Slider::draw_digit(Cairo::RefPtr<Cairo::Context>& cc, char digit) {
  cc->save();
  cc->set_source_rgb(0.7, 0.9, 1.0);
  cc->set_line_width(1);
  
  int width = 0;
  
  switch (digit) {
  case '0':
    cc->rel_line_to(3, 0);
    cc->rel_line_to(0, 6);
    cc->rel_line_to(-3, 0);
    cc->rel_line_to(0, -6);
    width = 5;
    break;
    
  case '1':
    cc->rel_move_to(3, 0);
    cc->rel_line_to(0, 6);
    width = 5;
    break;
    
  case '2':
    cc->rel_line_to(3, 0);
    cc->rel_line_to(0, 3);
    cc->rel_line_to(-3, 0);
    cc->rel_line_to(0, 3);
    cc->rel_line_to(3, 0);
    width = 5;
    break;
    
  case '3':
    cc->rel_line_to(3, 0);
    cc->rel_line_to(0, 6);
    cc->rel_line_to(-3, 0);
    cc->rel_move_to(0, -3);
    cc->rel_line_to(3, 0);
    width = 5;
    break;
    
  case '4':
    cc->rel_line_to(0, 3);
    cc->rel_line_to(3, 0);
    cc->rel_move_to(0, -3);
    cc->rel_line_to(0, 6);
    width = 5;
    break;
    
  case '5':
    cc->rel_move_to(3, 0);
    cc->rel_line_to(-3, 0);
    cc->rel_line_to(0, 3);
    cc->rel_line_to(3, 0);
    cc->rel_line_to(0, 3);
    cc->rel_line_to(-3, 0);
    width = 5;
    break;
    
  case '6':
    cc->rel_move_to(3, 0);
    cc->rel_line_to(-3, 0);
    cc->rel_line_to(0, 6);
    cc->rel_line_to(3, 0);
    cc->rel_line_to(0, -3);
    cc->rel_line_to(-3, 0);
    width = 5;
    break;
    
  case '7':
    cc->rel_line_to(3, 0);
    cc->rel_line_to(0, 6);
    width = 5;
    break;
    
  case '8':
    cc->rel_line_to(3, 0);
    cc->rel_line_to(0, 6);
    cc->rel_line_to(-3, 0);
    cc->rel_line_to(0, -6);
    cc->rel_move_to(0, 3);
    cc->rel_line_to(3, 0);
    width = 5;
    break;
    
  case '9':
    cc->rel_move_to(0, 6);
    cc->rel_line_to(3, 0);
    cc->rel_line_to(0, -6);
    cc->rel_line_to(-3, 0);
    cc->rel_line_to(0, 3);
    cc->rel_line_to(3, 0);
    width = 5;
    break;
    
  case '.':
    cc->rel_move_to(0, 6);
    cc->rel_line_to(0, -1);
    width = 2;
    break;
    
  case '*':
    cc->rel_move_to(0, 1);
    cc->rel_line_to(3, 4);
    cc->rel_move_to(-3, 0);
    cc->rel_line_to(3, -4);
    cc->rel_move_to(-3, 2);
    cc->rel_line_to(3, 0);
    width = 5;
    break;
    
  case '-':
    cc->rel_move_to(0, 3);
    cc->rel_line_to(3, 0);
    width = 5;
    break;
    
  }
  
  cc->stroke();
  cc->restore();
  
  return width;
}


void Slider::draw_string(Cairo::RefPtr<Cairo::Context>& cc, const std::string& str, float x, float y) {
  cc->move_to(x, y);
  int xoffset = 0;
  for (int i = 0; i < str.length(); ++i) {
    xoffset += draw_digit(cc, str[i]);
    cc->move_to(x + xoffset, y);
  }
}

*/

double Slider::map_to_adj(double knob) {
  double a = m_params[0].get_lower();
  double b = m_params[0].get_upper();
  knob = knob < 0 ? 0 : knob;
  knob = knob > 1 ? 1 : knob;
  if (m_logarithmic)
    return a * pow(b / a, knob);
  else
    return a + knob * (b - a);
}


double Slider::map_to_knob(double adj) {
  double a = m_params[0].get_lower();
  double b = m_params[0].get_upper();
  adj = adj < a ? a : adj;
  adj = adj > b ? b : adj;
  if (m_logarithmic)
    return log(adj / a) / log(b / a);
  else
    return (adj - a) / (b - a);
}

} //namespace CloWidget

