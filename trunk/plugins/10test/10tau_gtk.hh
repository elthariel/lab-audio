/*
** 10tau_gtk.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Mon Jan 22 05:27:18 2007 Nahlwe
** $Id$
**
** Copyright (C) 2007 Nahlwe
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#ifndef   	TAU_GTK_HH_
# define   	TAU_GTK_HH_

#include <gtkmm.h>
#include "10tau.peg"
#include "lv2gtk2gui.hpp"


class TauGUI : public LV2GTK2GUI
{
public:
  TauGUI(LV2Controller& controller, const char* plugin_URI,
          const char* bundle_path, Gtk::Widget*& widget);

  bool                  chg_param_1(Gtk::ScrollType,
                                    double val);
  bool                  chg_param_2(Gtk::ScrollType,
                                    double val);
private:
  LV2Controller         &m_ctrl;

  Gtk::HBox             m_hbox;
  Gtk::Adjustment       m_adj1;
  Gtk::Adjustment       m_adj2;
  Gtk::VScale           m_scale1;
  Gtk::VScale           m_scale2;
};

#endif	    /* !10TAU_GTK_HH_ */
