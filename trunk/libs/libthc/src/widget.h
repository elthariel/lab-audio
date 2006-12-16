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
#include <libxml++/libxml++.h>

namespace Thc {

  using boost::shared_ptr;
  using Gtk::Adjustment;
  
  enum WidgetMode {
    ModeNormal = 1,
    ModeSlime = 2,
    ModeConnect = 4
  };

  typedef shared_ptr<Adjustment> Param;
  typedef shared_ptr<xmlpp::Node> Skins;
  //typedef shared_ptr<std::vector<shared_ptr<Gdk::PixBuf> > > ImageCollection;
  
  //all widget should support this interface
  class IWidget {
  public:
    inline IWidget(shared_ptr<xmlpp::Node> node):m_config(node), m_mode(ModeNormal), m_supported_mode(ModeNormal) {}
    inline IWidget(): m_mode(ModeNormal), m_supported_mode(ModeNormal) {}
  
  //## Parameters ##
  public:
	  inline int count_param()const { return m_params.size(); }
	  inline Param& get_param(int id) { return m_params[id]; }
  protected:
 	  inline void add_param(double value, double min, double max) { m_params.push_back(Param(new Adjustment(value, min, max))); }
		

  //## Widget Mode ##
  public:
    inline void set_mode(WidgetMode mode) { m_mode = mode; on_mode_change(); }
    inline int get_supported_mode()const { return m_supported_mode; }
    inline void add_supported_mode(WidgetMode mode) { m_supported_mode &= mode; } 
  protected:
    //TODO: signal
    virtual void on_mode_change() {};

  //## Skin ##
  public:
    //TODO: add the image collection parameter
    //a skin is just a xmlnode, and an image collection
    inline void set_skin(Skins node/*, shared_ptr<std::vector<Gdk::Pixbuf>>*/ )
      { m_config = node; on_skin_change(); }
  protected:
    //TODO: signal
    virtual void on_skin_change() {};
    
    
    
    
    
    
  //## Data ##
  protected:
    //all parameters
    std::vector<Param> m_params;
    
    //the current mode, and all supported mode
    WidgetMode m_mode;
    int m_supported_mode;
    
    //the skin configuration
    Skins m_config;
    //image collection associated with the skin
    //shared_ptr<imagecollection> m_images;
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
