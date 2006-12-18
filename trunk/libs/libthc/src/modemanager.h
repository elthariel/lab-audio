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
// Class: ModeManager
// Created by: GESTES Cedric <goctaf@gmail.com>
// Created on: Sun Dec  3 19:34:17 2006
//

#ifndef _MODEMANAGER_H_
#define _MODEMANAGER_H_

namespace Thc {

  //regroup widget by group
  //allow to toggle their mode (Connect/Normal)
  class ModeManager: {
  public:
    //add_widget(const Glib::ustring &group, Widget::Ref widget);
    //toggle_mode(const Glib::ustring &group, WidgetMode mode);
  
    inline static void instanciate() { if (!m_mode_manager) m_mode_manager = new ModeManager(); }
    inline static ModeManager& instance() { return m_mode_manager; }
  protected:
    ModeManager() {};
    
  private:
    static ModeManager m_mode_manager;
    //list
  };
}

#endif

