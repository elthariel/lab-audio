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
// Class: WidgetManager
// Created by: GESTES Cedric <goctaf@gmail.com>
// Created on: Sun Dec  3 19:34:17 2006
//

#ifndef _WIDGETMANAGER_H_
#define _WIDGETMANAGER_H_

#include <map>
#include <vector>
#include <gtkmm.h>
#include "ithcwidget.h"
//#include "lo/lo.h"

namespace Thc {
  
  template <typename T>
  class Singleton {
  public:
    typedef T typename;
  
    inline static void instanciate() { if (!m_ref) m_ref = new T(); }
    inline static T *instance() { return m_ref; }

  private:
    virtual Singleton() {};
    static T *m_ref;
  };
  
  class WidgetManager: public Singleton<WidgetManager> {
  public:
    typedef std::vector<IThcWidget *> Vector;
    typedef std::map<Glib::ustring, Vector> Map;
  
    //get_widget(const Glib::ustring &widget_name);
    
    //set_path(const Glib::ustring &widget_name, const Glib::ustring &path);
    //get_path(const Glib::ustring &widget_name);
    //inline get_path(const ThcWidget thc) { return get_path(thc->get_name()); }


    //set_mode_connect
    //set_mode_learn
    //set_mode_normal

  // "/widget36" "/component1/component23/widget36"  
//    typedef std::map<Glib::ustring, Glib::ustring> Map;
  };
}

#endif

