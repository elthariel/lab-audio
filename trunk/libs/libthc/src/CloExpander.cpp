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
//
// Created by: GESTES Cedric <goctaf@gmail.com>
// Created on: Sun Dec  3 19:34:17 2006
//

#include <gtkmm/expander.h>
#include <gtk/gtk.h>
#include "clowidget/CloExpander.h"

namespace CloWidget {

CloExpander::CloExpander() : Gtk::Expander() {
  set_expanded(true);
  add_events(Gdk::POINTER_MOTION_MASK);
	signal_event().connect(sigc::mem_fun(*this, &CloExpander::on_expander_event));
	drag = false;
	moved = false;
}

CloExpander::CloExpander(const Glib::ustring& label, bool mnemonic) : Gtk::Expander(label, mnemonic) {
  set_expanded(true);
  add_events(Gdk::POINTER_MOTION_MASK);
	signal_event().connect(sigc::mem_fun(*this, &CloExpander::on_expander_event));
	drag = false;
	moved = false;
}

bool CloExpander::on_expander_event(GdkEvent *ev) {
	Gtk::Layout *layout;

  if (ev->type == GDK_BUTTON_PRESS) {
    drag = true;
    origx = ((GtkWidget *)gobj())->allocation.x;
    origy = ((GtkWidget *)gobj())->allocation.y;
    lastx = (int)ev->button.x_root;
    lasty = (int)ev->button.y_root;
    moved = false;
  } else if (ev->type == GDK_MOTION_NOTIFY && drag) {
    origx += (int)ev->motion.x_root - lastx;
    lastx = (int)ev->motion.x_root;
    origy += (int)ev->motion.y_root - lasty;
    lasty = (int)ev->motion.y_root;
    moved = true;
    layout = dynamic_cast<Gtk::Layout *>(get_parent());
    if (layout)
      layout->move(*this, origx, origy);
  	return true;
  } else if (ev->type == GDK_BUTTON_RELEASE) {
    drag = false;
    return moved;
  }
  return false;
}

CloExpander::~CloExpander() {
}

}
