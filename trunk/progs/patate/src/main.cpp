/*
** main.cpp
** Login : <elthariel@elthariel-desktop>
** Started on  Wed Apr  4 00:00:29 2007 Nahlwe
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
#include "patate.hh"
#include "patate_gui.hh"
#include "lfringbuffer.hh"

using namespace std;
using namespace Gtk;

int     main(int ac, char **av)
{
  cout << "Creating msg queues" << endl;
  LFRingBuffer<Event>   *m_ring_gui2core = new LFRingBuffer<Event>(50);
  LFRingBuffer<Event>   *m_ring_core2gui = new LFRingBuffer<Event>(50);
  cout << "Creating patate object" << endl;
  Patate                *patate = new Patate(m_ring_core2gui->get_writer(),
                                             m_ring_gui2core->get_reader());
  cout << "Initialising gtk" << endl;
  Main                  kit(ac, av);
  cout << "Creating gui object" << endl;
  PatateGUI             *gui = new PatateGUI(m_ring_core2gui->get_reader(),
                                             m_ring_gui2core->get_writer(),
                                             *patate);
  cout << "Activtating jack client" << endl;
  patate->activate();
  cout << "Launching gui" << endl;


  Main::run(*gui);
}
