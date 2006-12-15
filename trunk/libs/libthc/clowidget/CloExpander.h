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
// Class: CloExpander
// Created by: GESTES Cedric <goctaf@gmail.com>
// Created on: Sun Dec  3 19:34:17 2006
//

#ifndef _CLOEXPANDER_H_
#define _CLOEXPANDER_H_
#include <gtkmm.h>
namespace CloWidget {


class CloExpander : public Gtk::Expander {
public:
	CloExpander();
	CloExpander(const Glib::ustring& label, bool mnemonic=false);
	~CloExpander();	
	
protected:
  virtual bool on_expander_event(GdkEvent *ev);
  
private:
  bool drag, moved;
  int lastx, lasty, origx, origy;
};

}

#endif	//_CLOEXPANDER_H_

