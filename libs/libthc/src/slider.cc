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

#include "slider.h"


namespace Thc {

using namespace std;


Slider::Slider(const Skin::RefSkin &skin)
  : IWidget(skin),
    m_integer(true),
    m_logarithmic(false),
    m_step(0),
    m_horizontal(true) {
}

Slider::Slider(float min, float max, float value, bool integer, bool logarithmic, bool horizontal)
  : m_integer(integer),
    m_logarithmic(logarithmic),
    m_step(0),
    m_horizontal(horizontal) {
  //add_supported_mode(ModeConnect);
  add_param("x", min, min, max);
  if (m_horizontal)
    set_size_request(64, 32);
  else
    set_size_request(32, 64);
  add_events(Gdk::EXPOSURE_MASK | Gdk::BUTTON1_MOTION_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::SCROLL_MASK);
  get_param("x")->signal_value_changed().connect(mem_fun(*this, &Slider::queue_draw));
  if (m_integer)
    m_step = 1.0 / (max - min);
  else
    m_step = 1.0 / 30;
  value = (value < min ? min : value);
  value = (value > max ? max : value);
  get_param("x")->set_value(value);

  Skin::RefSkin skin = Skin::create_skin();
  m_images_all = "../skins/bang/fader-%i.png";
  skin->set_images(m_images_all, Skin::create_images(m_images_all, 127));
  set_skin(skin);
}

void Slider::on_mode_change() {
  queue_draw();
}

//draw the slider with cairo
void Slider::draw_vector(GdkEventExpose* event, 
						 Glib::RefPtr<Gdk::GC> gc, 
						 Cairo::RefPtr<Cairo::Context> cc) {
  float value = get_param("x")->get_value();
	
  cc->move_to(event->area.x,event->area.y);
  cc->line_to(event->area.x,event->area.height);
  cc->line_to(event->area.width,event->area.height);
  cc->line_to(event->area.width,event->area.y);
  cc->line_to(event->area.x,event->area.y);

  if (m_integer)
    value = floor(value + 0.5);
  if (m_horizontal) {
    cc->move_to(0, (event->area.height) / 2);
    cc->line_to(event->area.width, (event->area.height) / 2);
    value = (value - get_param("x")->get_lower()) * (event->area.width - 3) / (get_param("x")->get_upper() - get_param("x")->get_lower());
    cc->move_to((int)value + 2, 2);
    cc->line_to((int)value + 2, event->area.height - 2);
  } else {
    cc->move_to(event->area.width / 2, 0);
    cc->line_to(event->area.width / 2, event->area.height);
    value = (value - get_param("x")->get_lower()) * (event->area.height - 3) / (get_param("x")->get_upper() - get_param("x")->get_lower());
    cc->move_to(2, (int)value + 2);
    cc->line_to(event->area.width - 2, (int)value + 2);
  }
  cc->stroke();
}

void Slider::draw_images(GdkEventExpose* event, 
						 Glib::RefPtr<Gdk::GC> gc, 
						 Cairo::RefPtr<Cairo::Context> cc) {
  float value = get_param("x")->get_value();
  if (m_integer)
    value = floor(value + 0.5);
  value = (value - get_param("x")->get_lower()) * (get_skin()->get_images_count(m_images_all)-1) / (get_param("x")->get_upper() - get_param("x")->get_lower());
  Glib::RefPtr<Gdk::Pixbuf> image = get_skin()->get_images(m_images_all, (int)value);
  if (image)  //deprecated, need clipping, need scale, etc...
    image->render_to_drawable(get_window(), gc, 0, 0, 0, 0, image->get_width(), image->get_height(), Gdk::RGB_DITHER_NONE, 0, 0);
}

//background/handle
//background/foreground
void Slider::draw_2images(GdkEventExpose* event, 
						  Glib::RefPtr<Gdk::GC> gc, 
						  Cairo::RefPtr<Cairo::Context> cc) {
												  
}
												  

bool Slider::on_expose_event(GdkEventExpose* event) {
  
  Glib::RefPtr<Gdk::Window> win = get_window();
  Glib::RefPtr<Gdk::GC> gc = Gdk::GC::create(win);
  Cairo::RefPtr<Cairo::Context> cc = win->create_cairo_context();
  
  cc->set_line_join(Cairo::LINE_JOIN_ROUND);
  if (get_mode() == ModeNormal) {
  	//draw_vector(event, gc, cc);
  	draw_images(event, gc, cc);
  } else if (get_mode() == ModeConnect) {
  	cc->move_to(0, 0);
  	cc->line_to(event->area.width, event->area.height);
  	cc->move_to(event->area.width, 0);
  	cc->line_to(0, event->area.height);
  	cc->stroke();
  }
  return true;
}

bool Slider::on_motion_notify_event(GdkEventMotion* event) {
  float scale = 200;
  float value;
  
  if (event->state & GDK_SHIFT_MASK)
    scale *= 200;
  if (m_horizontal)
    value = m_value_offset + ((m_click_offset - event->x) / scale);
  else
    value = m_value_offset + ((m_click_offset - event->y) / scale);
  value = value < 0 ? 0 : value;
  value = value > 1 ? 1 : value;
  get_param("x")->set_value(map_to_adj(value));
  return true;
}

bool Slider::on_button_press_event(GdkEventButton* event) {
  if (m_horizontal)
    m_click_offset = (int)event->x;
  else
    m_click_offset = (int)event->y;
  m_value_offset = map_to_knob(get_param("x")->get_value());
  return true;
}

bool Slider::on_scroll_event(GdkEventScroll* event) {
  double step = m_step;
  if (event->state & GDK_SHIFT_MASK && !m_integer)
    step *= 0.01;
  if (event->direction == GDK_SCROLL_UP)
    get_param("x")->set_value(map_to_adj(map_to_knob(get_param("x")->get_value()) + step));
  else if (event->direction == GDK_SCROLL_DOWN)
    get_param("x")->set_value(map_to_adj(map_to_knob(get_param("x")->get_value()) - step));
  return true;
}

//TODO REMOVE
double Slider::map_to_adj(double knob) {
  double a = get_param("x")->get_lower();
  double b = get_param("x")->get_upper();
  knob = knob < 0 ? 0 : knob;
  knob = knob > 1 ? 1 : knob;
  if (m_logarithmic)
    return a * pow(b / a, knob);
  else
    return a + knob * (b - a);
}

double Slider::map_to_knob(double adj) {
  double a = get_param("x")->get_lower();
  double b = get_param("x")->get_upper();
  adj = adj < a ? a : adj;
  adj = adj > b ? b : adj;
  if (m_logarithmic)
    return log(adj / a) / log(b / a);
  else
    return (adj - a) / (b - a);
}

} //namespace Thc

