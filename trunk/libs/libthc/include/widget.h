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
// Class: ICloWidget
// Created by: GESTES Cedric <goctaf@gmail.com>
// Created on: Sun Dec  3 19:34:17 2006
//

#ifndef _WIDGET_H_
#define _WIDGET_H_
#include <gtkmm.h>
#include <vector>

namespace Thc {

  enum WidgetMode {
    ModeNormal = 1,
    ModeSlime = 2,
    ModeConnect = 4
  };


  //One Parameter
/*  class Parameter {
  public:
    void set_value(void* new_value) { value = new_value; }
    double get_value() { return value; }
    
  protected:
  
  private:
    //value_changed signal
    double value;
  };
*/

/*  template <class T> 
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

  //all widget should support this interface
  class IWidget {
  public:
    inline IWidget(): m_mode(ModeNormal), m_supported_mode(ModeNormal) {}
	//Parameters
	inline int count_param()const { return m_params.size(); }
	inline Gtk::Adjustment& get_param(int id) { return m_params[id]; }
	
	//Skins
	
    //Widget Mode
    virtual void on_mode_change() = 0;
    inline void set_mode(WidgetMode mode) { m_mode = mode; on_mode_change(); }
    inline int get_supported_mode()const { return m_supported_mode; }

  protected:
    //Parameters
    std::vector<Gtk::Adjustment&> m_params;
 
    //Skins
       
    //Widget Mode
    WidgetMode m_mode;
    int m_supported_mode;
};

}

#endif
