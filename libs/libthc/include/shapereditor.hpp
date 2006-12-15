/****************************************************************************
    
    shapereditor.hpp - gtkmm widget for editing waveshaping functions
    
    Copyright (C) 2006  Lars Luthman <lars.luthman@gmail.com>
    
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA  02110-1301  USA

****************************************************************************/

#ifndef SHAPEREDITOR_HPP
#define SHAPEREDITOR_HPP

#include <string>
#include <vector>

#include <gtkmm.h>


class ShaperEditor : public Gtk::DrawingArea {
public:
  
  ShaperEditor();
  
  bool set_string(const std::string& str);
  std::string get_string() const;
  
  sigc::signal<void> signal_apply;
  
protected:

  struct Point {
    
    Point(double _x = 0, double _y = 1)
      : x(_x),
        y(_y) {

    }
    
    double x;
    double y;
  };
  
  
  bool on_expose_event(GdkEventExpose* event);
  bool on_motion_notify_event(GdkEventMotion* event);
  bool on_button_release_event(GdkEventButton* event);
  bool on_button_press_event(GdkEventButton* event);
  bool on_scroll_event(GdkEventScroll* event);
  
  void new_point();
  void delete_point();
  void set_dirty();
  void apply();
  
  double x2p(double x);
  double y2p(double y);
  double p2x(int p);
  double p2y(int p);
  
  double shape(double y);

  
  std::vector<Point> m_points;
  
  double m_margin;
  double m_click_x, m_click_y;
  int m_active_point;
  bool m_dragging;
  int m_pix_drag_x, m_pix_drag_y;
  double m_drag_x, m_drag_y;
  
  bool m_wave;
  
  bool m_dirty;
  
  Gtk::Menu m_menu;
  
};


#endif