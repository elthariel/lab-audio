/*
** main_win.hh
** Login : <lta@elthariel-main>
** Started on  Fri May 25 17:11:21 2007 Elthariel
** $Id$
**
** Copyright (C) 2007 Elthariel
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

#ifndef   	MAIN_WIN_HH_
# define   	MAIN_WIN_HH_

#include <gtkmm.h>

class MainWin : public Gtk::Window
{
public:
  MainWin();

  void                  unimplemented();
  void                  quit();
protected:
  void                  create_actions();

  Gtk::VBox                             m_vbox;
  Glib::RefPtr<Gtk::UIManager>          m_ui_manager;
  Glib::RefPtr<Gtk::ActionGroup>        m_action_group;
};

#endif	    /* !MAIN_WIN_HH_ */
