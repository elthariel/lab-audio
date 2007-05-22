/*
** synthview_generic.cc
** Login : <elthariel@elthariel-desktop>
** Started on  Sun May 20 13:07:54 2007 Nahlwe
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
#include "patate_gui.hh"

GenericSynthView::GenericSynthView(PatateGUI &a_gui,
                                   unsigned int a_track_id)
  : m_gui(a_gui),
    m_track_id(a_track_id)
{
}
