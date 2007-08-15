/*
** main.cc
** Login : <elthariel@elthariel-desktop>
** Started on  Wed Aug 15 00:44:50 2007 Nahlwe
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

#include <iostream>
#include <gtkmm/main.h>
#include <gtkmm/box.h>
#include <gtkmm/window.h>
#include <gtkmm/scrolledwindow.h>
#include "kbd_view.hh"
#include "roll_view.hh"

int main(int ac, char **av)
{
  Gtk::Main     kit(ac, av);

  Gtk::Window           win;
  Gtk::HBox             hbox;
  Gtk::ScrolledWindow   scroll;
  KbdView               kview(20, 45);
  RollView              rview(20, 15, 4, 4);

  win.add(scroll);
  scroll.add(hbox);
  hbox.pack_start(kview, Gtk::PACK_SHRINK);
  hbox.pack_start(rview);

  win.show_all();

  Gtk::Main::run(win);
}


