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
// Class: IThcWidget
// Created by: GESTES Cedric <goctaf@gmail.com>
// Created on: Sun Dec  3 19:34:17 2006
//

#ifndef _ITHCWIDGET_H_
#define _ITHCWIDGET_H_

#include "skin.h"
#include "param.h"

namespace Thc {

  enum WidgetMode {
    ModeNormal = 1,
    ModeLearn = 2,
    ModeConnect = 4,
  };
  
  class IThcWidget {
  //## Parameters ##
  public:
	virtual int get_param_count()const = 0;
	virtual Param::Ref get_param(const Glib::ustring& name) = 0;
//	virtual ~IThcWidget() = {};
  //## Widget Mode ##
  public:
    virtual void set_mode(WidgetMode mode) = 0;
    virtual WidgetMode get_mode()const = 0;
    virtual int get_supported_mode()const = 0;
    virtual sigc::signal<void>& signal_mode_change() = 0;

  //## Skin ##
  public:
    virtual void set_skin(const Skin::Ref &skin) = 0;
    virtual Skin::Ref get_skin()const = 0;
    virtual sigc::signal<void>& signal_skin_change() = 0;
  };
}
  
#endif

