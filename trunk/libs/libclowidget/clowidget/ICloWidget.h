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

#ifndef _ICLOWIDGET_H_
#define _ICLOWIDGET_H_
#include <gtkmm.h>

namespace CloWidget {
  enum CloWidgetMode {
    ModeNormal = 1,
    ModeSlime = 2,
    ModeConnect = 4
  };
  
//all widget should support this interface
class ICloWidget {
public:
  virtual void set_mode(CloWidgetMode mode) = 0;
  virtual CloWidgetMode get_supported_mode() = 0;
};

}

#endif
