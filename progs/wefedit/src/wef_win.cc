/*
** wef_win.cc
** Login : <elthariel@elthariel-desktop>
** Started on  Sun May 27 15:43:47 2007 Nahlwe
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
#include "wef_win.hh"

using namespace std;
using namespace Gtk;
using namespace sigc;

WefWin::WefWin(Wef &a_wef)
  : m_wef(a_wef),
    m_wefview(*new WefView(a_wef))
{
  add(m_vbox);

  m_scrolled_win.add(m_wefview);
  m_vbox.pack_start(m_scrolled_win);

  show_all();
}


