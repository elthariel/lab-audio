/*
** synthview_generic.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Sun May 20 12:55:29 2007 Nahlwe
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

#ifndef   	SYNTHVIEW_GENERIC_HH_
# define   	SYNTHVIEW_GENERIC_HH_

class PatateGUI;

class GenericSynthView : public Gtk::VBox
{
public:
  GenericSynthView(PatateGUI &a_gui,
                   unsigned int a_track_id);
protected:
  PatateGUI             &m_gui;
  unsigned int          m_track_id;
};

#endif	    /* !SYNTHVIEW_GENERIC_HH_ */
