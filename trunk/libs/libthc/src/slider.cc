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
  
         
Slider::Slider(Skin::Ref skin, Param::Ref param)
  : ThcWidget(skin),
    m_param(param) {
  init();
}

Slider::Slider(Param::Ref param, bool horizontal)
  : ThcWidget(),
    m_param(param),
    m_horizontal(horizontal),
    m_type(SliderVector) {
  init();
}

//constructor for images mode
Slider::Slider(Images::Ref images, Param::Ref param, bool horizontal)
  : ThcWidget(),
    m_images(images),
    m_param(param),
    m_horizontal(horizontal),
    m_type(SliderAll) {
  init();
  Image::Ref img = ((*images)[0]);
  if (img)
    set_size_request(img->get_width(), img->get_height());
}

//constructor for 2 images mode
Slider::Slider(Image::Ref image_background,
               Image::Ref image_foreground,
               Param::Ref param,
               SliderType type,
               bool horizontal)
  : ThcWidget(),
    m_image_background(image_background),
    m_image_foreground(image_foreground),
    m_param(param),
    m_type(type),
    m_horizontal(horizontal) {
  init();
  if (image_background)
    set_size_request(image_background->get_width(), image_background->get_height());  
}
       
void Slider::init() {
  set_param("x", m_param);
  m_param->signal_value_changed().connect(mem_fun(*this, &Slider::queue_draw));
  signal_mode_change().connect(mem_fun(*this, &Slider::queue_draw));
  add_events(Gdk::EXPOSURE_MASK | Gdk::BUTTON1_MOTION_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::SCROLL_MASK);
  m_step = 1.0 / (m_param->get_upper() - m_param->get_lower());
  if (m_horizontal)
    set_size_request(64, 32);
  else
    set_size_request(32, 64);  
}

//draw the slider with cairo
void Slider::draw_vector(GdkEventExpose* event, 
						 Glib::RefPtr<Gdk::GC> gc, 
						 Cairo::RefPtr<Cairo::Context> cc) {
  float value = m_param->get_value();
  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();
  

  
  cc->rectangle(0, 0, width, height);
  cc->stroke();
  if (m_horizontal) {
    cc->move_to(0, height / 2);
    cc->line_to(width, height / 2);
    cc->stroke();
    value = (value - m_param->get_lower()) * (width - 2 - 10) / (m_param->get_upper() - m_param->get_lower());
    cc->save();
    cc->set_source_rgb(0.3, 1.0, 0.0);
    cc->rectangle((int)value + 1, 1, 10, height - 2);
    cc->fill();
    cc->restore();
    cc->stroke();
  } else {
    cc->move_to(width / 2, 0);
    cc->line_to(width / 2, height);
    value = (value - m_param->get_lower()) * (height - 2 - 10) / (m_param->get_upper() - m_param->get_lower());
    cc->stroke();
    cc->save();
    cc->set_source_rgb(0.3, 1.0, 0.0);
    cc->rectangle(1, (int)value + 1, width - 2, 10);
    cc->fill();
    cc->restore();
    cc->stroke();
  }
  cc->stroke();
}

void Slider::draw_images(GdkEventExpose* event, 
						 Glib::RefPtr<Gdk::GC> gc, 
						 Cairo::RefPtr<Cairo::Context> cc) {
  float value = m_param->get_value();

  value = (value - m_param->get_lower()) * (m_images->size()-1) / (m_param->get_upper() - m_param->get_lower());
  Glib::RefPtr<Gdk::Pixbuf> image = (*m_images)[(int)value];
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

  //clip to what really need to be redrawn
  cc->rectangle(event->area.x, event->area.y, event->area.width, event->area.height);
  cc->clip();
    
  cc->set_line_join(Cairo::LINE_JOIN_ROUND);
  if (get_mode() == ModeNormal) {
  	if (m_type == SliderVector)
  	  draw_vector(event, gc, cc);
  	else if (m_type == SliderAll)
  	  draw_images(event, gc, cc);
  } else if (get_mode() == ModeConnect) {
    draw_ports(get_allocation(), cc);
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
  m_param->set_value(map_to_adj(value));
  return true;
}

bool Slider::on_button_press_event(GdkEventButton* event) {
  if (m_horizontal)
    m_click_offset = (int)event->x;
  else
    m_click_offset = (int)event->y;
  m_value_offset = map_to_knob(m_param->get_value());
  return true;
}

bool Slider::on_scroll_event(GdkEventScroll* event) {
  double step = m_step;
  if (event->state & GDK_SHIFT_MASK /*&& !m_integer*/)
    step *= 0.01;
  if (event->direction == GDK_SCROLL_UP)
    m_param->set_value(map_to_adj(map_to_knob(m_param->get_value()) + step));
  else if (event->direction == GDK_SCROLL_DOWN)
    m_param->set_value(map_to_adj(map_to_knob(m_param->get_value()) - step));
  return true;
}

//TODO REMOVE
double Slider::map_to_adj(double knob) {
  double a = m_param->get_lower();
  double b = m_param->get_upper();
  knob = knob < 0 ? 0 : knob;
  knob = knob > 1 ? 1 : knob;
/*  if (m_logarithmic)
    return a * pow(b / a, knob);
  else*/
    return a + knob * (b - a);
}

double Slider::map_to_knob(double adj) {
  double a = m_param->get_lower();
  double b = m_param->get_upper();
  adj = adj < a ? a : adj;
  adj = adj > b ? b : adj;
/*  if (m_logarithmic)
    return log(adj / a) / log(b / a);
  else*/
    return (adj - a) / (b - a);
}

} //namespace Thc

