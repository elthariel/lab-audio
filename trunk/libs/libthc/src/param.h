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
// Class: Param
// Created by: GESTES Cedric <goctaf@gmail.com>
// Created on: Sun Dec  3 19:34:17 2006
//

#ifndef _PARAM_H_
#define _PARAM_H_
#include <gtkmm.h>
#include <vector>
#include <boost/shared_ptr.hpp>

namespace Thc {

  //warper around Gtk::Adjustment
  class Param {
  public:
	Param(double min = 0., double max = 10., double value = 5.): m_adj(min, max, value) {}
    typedef boost::shared_ptr<Param> Ref;
    
    inline Glib::SignalProxy0<void> signal_value_changed() { return m_adj.signal_value_changed(); };
    inline double get_value() { return m_adj.get_value(); }
    inline void set_value(double value) { return m_adj.set_value(value); }
    inline double get_lower() { return m_adj.get_lower(); }
    inline double get_upper() { return m_adj.get_upper(); }
    
    //inline Gtk::Adjustment get_adj()const { return m_adj; };
    static Ref create_param(double min = 0., double max = 10., double value = 5.);
    
  private:
    Gtk::Adjustment m_adj;
  };
  
}

#endif
