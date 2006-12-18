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
  enum SliderType { SliderAll, SliderForeground, SliderHandle, SliderVector };
  
  //constructor taking a xml dom as parameter
  Slider(Skin::Ref skin, Param::Ref param = Param::create_param());

  //constructor for vectorial mode
  Slider(Param::Ref param = Param::create_param(), bool horizontal = true);
 
  //constructor for images mode
  Slider(Skin::RefImages images, Param::Ref param = Param::create_param(), bool horizontal = true);

  //constructor for 2 images mode
  Slider(Skin::RefImage images_background,
         Skin::RefImage images_foreground,
         Param::Ref param = Param::create_param(),
         SliderType type = SliderForeground,
         bool horizontal = true);

protected:
  bool on_expose_event(GdkEventExpose* event);
  bool on_motion_notify_event(GdkEventMotion* event);
  bool on_button_press_event(GdkEventButton* event);
  bool on_scroll_event(GdkEventScroll* event);
  
  void draw_vector(GdkEventExpose* event, Glib::RefPtr<Gdk::GC> gc, Cairo::RefPtr<Cairo::Context> cc);
  void draw_images(GdkEventExpose* event, Glib::RefPtr<Gdk::GC> gc, Cairo::RefPtr<Cairo::Context> cc);
  void draw_2images(GdkEventExpose* event, Glib::RefPtr<Gdk::GC> gc, Cairo::RefPtr<Cairo::Context> cc);
												  
  //IWidget
  void on_mode_change();

  void init();

  //should be elsewhere maybe into Thc::Parameter
  double map_to_adj(double knob);
  double map_to_knob(double adj);
  
private:
  int m_click_offset;
  float m_value_offset;
  float m_red, m_green, m_blue;
  bool m_integer;
  bool m_logarithmic;
  bool m_horizontal;
  float m_step;

  SliderType m_type;
  Param::Ref m_param;
  Skin::RefImage m_image_background;
  Skin::RefImage m_image_foreground;
  Skin::RefImage m_image_handler;
  Skin::RefImages m_images;
};


} //namespace Thc

#endif	//_SLIDER_H_
