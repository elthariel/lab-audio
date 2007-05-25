/*
** main.cc
** Login : <lta@elthariel-main>
** Started on  Fri May 25 17:12:31 2007 Elthariel
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

#include <iostream>
#include "main_win.hh"

using namespace std;
using namespace Gtk;
using namespace sigc;

int main (int ac, char **av)
{
  Main          kit(ac, av);

  MainWin       win;

  Main::run(win);
}

