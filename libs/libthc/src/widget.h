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

#ifndef _WIDGET_H_
#define _WIDGET_H_
#include <gtkmm.h>
#include <vector>
#include <boost/shared_ptr.hpp>
//#include <libxml++/libxml++.h>

#include "skin.h"
#include "param.h"

namespace Thc {

  using boost::shared_ptr;
  using Gtk::Adjustment;
  
  enum WidgetMode {
    ModeNormal = 1,
    ModeSlime = 2,
    ModeConnect = 4
  };
  
  //all widget should support this interface
  class IWidget {
  public:
  
    inline IWidget(Skin::Ref skin = Skin::Ref())
      : m_skin(skin),
        m_mode(ModeNormal),
        m_supported_mode(ModeNormal & ModeConnect) {}

  //## Parameters ##
  public:
	  inline int count_param()const { return m_params.size(); }
	  inline Param::Ref get_param(const Glib::ustring& name) { return m_params[name]; }
  protected:
 	  inline void set_param(const Glib::ustring& name, Param::Ref param) { m_params[name] = param; }
		

  //## Widget Mode ##
  public:
    inline void set_mode(WidgetMode mode) { m_mode = mode; on_mode_change(); signal_mode_change(); }
    inline WidgetMode get_mode()const { return m_mode; }
    inline int get_supported_mode()const { return m_supported_mode; }
  protected:
    inline void add_supported_mode(WidgetMode mode) { m_supported_mode &= mode; } 
    virtual void on_mode_change() {};
    sigc::signal<void> signal_mode_change;

  //## Skin ##
  public:
    //TODO: add the image collection parameter
    //a skin is just a xmlnode, and an image collection
    inline void set_skin(const Skin::Ref &skin) { m_skin = skin; on_skin_change(); signal_skin_change(); }
    inline Skin::Ref get_skin()const { return m_skin; }
    
  protected:
    virtual void on_skin_change() {};
    sigc::signal<void> signal_skin_change;

  //## Data ##
  private:
    //all parameters
    std::map<Glib::ustring, Param::Ref> m_params;
    
    //the current mode, and all supported mode
    WidgetMode m_mode;
    int m_supported_mode;

    //the current skin config
    Skin::Ref m_skin;
};


/*
  //One Parameter
  class Parameter {
  public:
    void set_value(void* new_value) { value = new_value; }
    double get_value() { return value; }
    
  protected:
  
  private:
    //value_changed signal
    Gtk::Adjustment m_adj;
  };


  template <class T> 
  class Parameter {
  public:
    Parameter(float min, float max);
    inline void set_value(T& value) { m_value = value; }
    inline T& get_value()const { return m_value; }
    inline Gtk::Adjustment& get_adjustment()const { return m_adj; }
  protected:
  
  private:
    //value_changed signal
    T m_value;
    Gtk::Adjustment m_adj;
  };*/





}

#endif
