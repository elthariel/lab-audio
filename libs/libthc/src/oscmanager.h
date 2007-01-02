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
// Class: OscManager
// Created by: GESTES Cedric <goctaf@gmail.com>
// Created on: Sun Dec  3 19:34:17 2006
//

#ifndef _OSCMANAGER_H_
#define _OSCMANAGER_H_

#include <map>
#include <vector>
#include <gtkmm.h>
#include "ithcwidget.h"
#include "lo/lo.h"

namespace Thc {
  
  /** /widget/widgetname/paramname/set_value
   *  /widget/widgetname/paramname/get_value
   *  /widget/widgetname/paramname/set_adj
   *  /widget/widgetname/paramname/get_adj
   *  /widget/widgetname/get_param_count
   *  /widget/widgetname/get_param_name
   *  /widget/drag
   *  /widget/drop
   */
  
  
/* Some boilerplate killing macros... */
  #define LO_HANDLER_ARGS const char* path, const char* types, lo_arg** argv, int argc, lo_message msg

/* Defines a static handler to be passed to lo_add_method, which is a trivial
 * wrapper around a non-static method that does the real work.  Makes a whoole
 * lot of ugly boiler plate go away */
  #define LO_HANDLER(name) \
    int m_##name##_cb (LO_HANDLER_ARGS);\
    inline static int name##_cb(LO_HANDLER_ARGS, void* myself)\
    { return ((OSCEngineReceiver*)myself)->m_##name##_cb(path, types, argv, argc, msg); }

  class OscManager {
  public:
    typedef std::vector<IThcWidget *> Vector;
    typedef std::map<Glib::ustring, Vector> Map;
  
    inline static void instanciate() { if (!m_osc_manager) m_osc_manager = new OscManager(); }
    inline static OscManager *instance() { return m_osc_manager; }
    
  protected:
    OscManager() {};
    static void error_cb(int num, const char* msg, const char* path);
	  static int  set_response_address_cb(LO_HANDLER_ARGS, void* myself);
	  static int  generic_cb(LO_HANDLER_ARGS, void* myself);
	  static int  unknown_cb(LO_HANDLER_ARGS, void* myself);
	    
  private:
  	Glib::ustring m_port;
	  lo_server m_server;
    static OscManager *m_osc_manager;
    //list
  };
}

#endif

