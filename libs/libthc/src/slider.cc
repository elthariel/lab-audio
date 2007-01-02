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
  
         
Slider::Slider(Skin::Ref skin, Param::Ref param, bool scale, bool infinite)
  : ThcWidget<Gtk::DrawingArea>("slider", skin),
    m_param(param),
    m_scale(scale),
    m_infinite(infinite) {
  init();
  if (skin)
    on_skin_change();
}

Slider::Slider(Param::Ref param, bool horizontal, bool scale, bool infinite)
  : ThcWidget<Gtk::DrawingArea>("slider"),
    m_param(param),
    m_horizontal(horizontal),
    m_type(SliderVector),
    m_infinite(infinite),
    m_scale(scale) {
  init();
}

//constructor for images mode
Slider::Slider(Images::Ref images, Param::Ref param, bool horizontal, bool scale, bool infinite)
  : ThcWidget<Gtk::DrawingArea>("slider"),
    m_images(images),
    m_param(param),
    m_horizontal(horizontal),
    m_type(SliderAll),
    m_scale(scale),
    m_infinite(infinite) {
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
               bool horizontal,
               bool scale,
               bool infinite)
  : ThcWidget<Gtk::DrawingArea>("slider"),
    m_image_background(image_background),
    m_image_foreground(image_foreground),
    m_param(param),
    m_type(type),
    m_horizontal(horizontal),
    m_scale(scale),
    m_infinite(infinite) {
  init();
  if (image_background)
    set_size_request(image_background->get_width(), image_background->get_height());  
}

Slider::SliderType text2type(const Glib::ustring &str) {
  if (str == "all")
    return Slider::SliderAll;
  else if (str == "handle")
    return Slider::SliderHandle;
  else if (str == "foreground")
    return Slider::SliderForeground;
  else
    return Slider::SliderVector;
}

void Slider::on_skin_change() {
  Image::Ref img;
  if (!get_skin())
    return;
  m_type = text2type(get_skin()->get_attribute("render"));
  m_horizontal = get_skin()->get_bool_attribute("horizontal");
  switch (m_type) {
    case SliderVector:     
      break;
    case SliderAll:
      m_images = get_skin()->get_images("all");
      img = ((*m_images)[0]);
      if (img)
        set_size_request(img->get_width(), img->get_height());
      break;
    case SliderHandle:
      m_image_background = get_skin()->get_image("background");
      if (m_image_background)
        set_size_request(m_image_background->get_width(), m_image_background->get_height());
      m_image_foreground = get_skin()->get_image("handle");
      break;
    case SliderForeground:
      m_image_background = get_skin()->get_image("background");
      if (m_image_background)
        set_size_request(m_image_background->get_width(), m_image_background->get_height());
      m_image_foreground = get_skin()->get_image("foreground");
      break;
  }
  queue_draw();
}
     
void Slider::init() {
  set_param("x", m_param);
  m_param->signal_value_changed().connect(mem_fun(*this, &Slider::queue_draw));
  signal_mode_change().connect(mem_fun(*this, &Slider::queue_draw));
  add_events(Gdk::EXPOSURE_MASK |
             Gdk::BUTTON1_MOTION_MASK | 
             Gdk::BUTTON_PRESS_MASK | 
             Gdk::SCROLL_MASK |
             Gdk::ENTER_NOTIFY_MASK |
             Gdk::LEAVE_NOTIFY_MASK);
  m_step = 1.0 / (m_param->get_upper() - m_param->get_lower());
  m_mouseover = false;
  if (m_horizontal)
    set_size_request(64, 32);
  else
    set_size_request(32, 64);
  std::cout << "widget name:" <<  get_name() << std::endl;  
}

//draw the slider with cairo
void Slider::draw_vector(GdkEventExpose* event, 
						 Cairo::RefPtr<Cairo::Context> cc) {
  float value = m_param->get_value();
  Gtk::Allocation allocation = get_allocation();
  int width;
  int height;
  if (m_scale) {
    height = allocation.get_height();
    width = allocation.get_width();
  } else
    get_size_request(width, height);
  
  cc->set_source_rgb(1.0, 1.0, 1.0);
  cc->rectangle(0, 0, width, height);
  cc->rectangle(1, 1, width - 2, height - 2);
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
						 Cairo::RefPtr<Cairo::Context> cc) {
  float value = m_param->get_value();
  double w, h;

  value = (value - m_param->get_lower()) * (m_images->size()-1) / (m_param->get_upper() - m_param->get_lower());

  Image::Ref image = (*m_images)[(int) value];
  if (!image)
    return;
  w = image->get_width();
  h = image->get_height();

  cc->save();
  if (m_scale)
    cc->scale ((double)get_allocation().get_width()/w, (double)get_allocation().get_height()/h);
  cc->set_source(image, 0, 0);
  cc->paint();
  cc->stroke();
  cc->restore();
}

//background/handle
//background/foreground
void Slider::draw_2images(GdkEventExpose* event, 
						  Cairo::RefPtr<Cairo::Context> cc) {
  double w, h;
  float value = m_param->get_value();

  cc->save();
  if (!m_image_background)
    return;
  w = m_image_background->get_width();
  h = m_image_background->get_height();
  if (m_scale)
    cc->scale ((double)get_allocation().get_width()/w, (double)get_allocation().get_height()/h);
  cc->set_source(m_image_background, 0, 0);
  cc->paint();
  cc->stroke();
  
  if (!m_image_foreground)
    return;
  //draw the handle
  if (m_type == SliderHandle) {
    if (m_horizontal) {
      value = (value - m_param->get_lower()) 
              * (w - m_image_foreground->get_width())//(m_images->size()-1) 
              / (m_param->get_upper() - m_param->get_lower());
      cc->set_source(m_image_foreground, value, 0);
    } else {
      value = (value - m_param->get_lower()) 
              * (h - m_image_foreground->get_height())//(m_images->size()-1) 
              / (m_param->get_upper() - m_param->get_lower());
      cc->set_source(m_image_foreground, 0, value);
    }
    cc->paint();
    cc->stroke();
  }
  cc->restore();
}
												  

bool Slider::on_expose_event(GdkEventExpose* event) {
  
  Glib::RefPtr<Gdk::Window> win = get_window();
  Cairo::RefPtr<Cairo::Context> cc = win->create_cairo_context();

  //clip to what really need to be redrawn
  cc->rectangle(event->area.x, event->area.y, event->area.width, event->area.height);
  cc->clip();
    
  cc->set_line_join(Cairo::LINE_JOIN_ROUND);
  if (get_mode() == ModeNormal) {
  	if (m_type == SliderVector)
  	  draw_vector(event, cc);
  	else if (m_type == SliderAll)
  	  draw_images(event, cc);
  	else
  	  draw_2images(event, cc);
  } else if (get_mode() == ModeConnect) {
    draw_ports(get_allocation(), cc);
  }
  if (m_mouseover) {
    cc->set_source_rgba(0.8, 0.8, 0.0, 0.5);
    if (m_scale)
      cc->rectangle(0, 0, get_allocation().get_width(), get_allocation().get_height());
    else {
      int h,w;
      get_size_request(w, h);
      cc->rectangle(0, 0, w, h);     
    }
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

bool Slider::on_enter_notify_event(GdkEventCrossing* event) {
  m_mouseover = true;
  queue_draw();
}

bool Slider::on_leave_notify_event(GdkEventCrossing* event) {
  m_mouseover = false;
  queue_draw();
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

