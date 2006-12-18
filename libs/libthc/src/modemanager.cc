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
//
// Created by: GESTES Cedric <goctaf@gmail.com>
// Created on: Sun Dec  3 19:34:17 2006
//

#include "modemanager.h"

namespace Thc {
  ModeManager* ModeManager::m_mode_manager = 0;
  
  void ModeManager::add_widget(const Glib::ustring &group, IThcWidget &widget) {
    add_widget(group, &widget);
  }

  void ModeManager::add_widget(const Glib::ustring &group, IThcWidget *widget) {
    m_group[group].push_back(widget);
  }

  void ModeManager::remove_widget(IThcWidget &widget) {
    remove_widget(&widget);
  }
  
  void ModeManager::remove_widget(IThcWidget *widget){
    Map::iterator itmap;
    for (itmap = m_group.begin(); itmap != m_group.end(); itmap++) {
      Vector::iterator it = find((*itmap).second.begin(), (*itmap).second.end(), widget);
      if (it != (*itmap).second.end()) {
        (*itmap).second.erase(it);
      }
    }
  }
  
  void ModeManager::set_mode(const Glib::ustring &group, WidgetMode mode) {
    Vector &vector = m_group[group];
    Vector::iterator it;

	for (it = vector.begin(); it != vector.end(); it++) {
	  if (*it != NULL)
	    (*it)->set_mode(mode);
	}
  }
  
}

