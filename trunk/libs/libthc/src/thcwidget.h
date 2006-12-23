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
// Class: IWidget
// Created by: GESTES Cedric <goctaf@gmail.com>
// Created on: Sun Dec  3 19:34:17 2006
//

#ifndef _THCWIDGET_H_
#define _THCWIDGET_H_
#include <gtkmm.h>
#include <vector>
#include <boost/shared_ptr.hpp>
//#include <libxml++/libxml++.h>
#include "ithcwidget.h"
#include "skin.h"
#include "param.h"
#include "modemanager.h"
#include "cairoutils.h"

namespace Thc {
  
  template <class T>
  class ThcWidget: public IThcWidget, public T {
  public:
    //typedef typename T BaseClass;
    ThcWidget(Skin::Ref skin = Skin::Ref());
    virtual ~ThcWidget();

  public:
	inline int get_param_count()const { return m_params.size(); }
	inline Param::Ref get_param(const Glib::ustring& name) { return m_params[name]; }
  protected:
 	inline void set_param(const Glib::ustring& name, Param::Ref param) { m_params[name] = param; }
		
  public:
    inline void set_mode(WidgetMode mode) { m_mode = mode; on_mode_change(); m_signal_mode_change(); }
    inline WidgetMode get_mode()const { return m_mode; }
    inline int get_supported_mode()const { return m_supported_mode; }
    inline sigc::signal<void>& signal_mode_change() { return m_signal_mode_change; }
  protected:
    inline void add_supported_mode(WidgetMode mode) { m_supported_mode &= mode; } 
    virtual void on_mode_change() {};
    void draw_ports(const Gtk::Allocation &allocation, Cairo::RefPtr<Cairo::Context> cc);

  public:
    inline void set_skin(const Skin::Ref &skin) { m_skin = skin; on_skin_change(); m_signal_skin_change(); }
    inline Skin::Ref get_skin()const { return m_skin; }
    inline sigc::signal<void>& signal_skin_change() { return m_signal_skin_change; }
  protected:
    virtual void on_skin_change() {};

  private:
    std::map<Glib::ustring, Param::Ref> m_params;
    WidgetMode m_mode;
    int m_supported_mode;
    sigc::signal<void> m_signal_mode_change;
    sigc::signal<void> m_signal_skin_change;
    Skin::Ref m_skin;
};


  template <class T>
  ThcWidget<T>::ThcWidget(Skin::Ref skin)
    : T(),
      m_skin(skin),
      m_mode(ModeNormal),
      m_supported_mode(ModeNormal & ModeConnect) {
  }
  
  template <class T>
  ThcWidget<T>::~ThcWidget() {
    if (ModeManager::instance())
      ModeManager::instance()->remove_widget(this);
  }
  
  template <class T>
  void ThcWidget<T>::draw_ports(const Gtk::Allocation &allocation, Cairo::RefPtr<Cairo::Context> cc) {
    int x = 2, y = 2;
    const int width = allocation.get_width();
    const int height = allocation.get_height();
  
    cc->rectangle(0, 0, width, height);  
    cc->stroke();  
    for (int i = 0; i < get_param_count(); i++) {
      CairoUtils::draw_port(cc, x, y);
      x += 15;
    }
  }


} //namespace Thc

#endif
