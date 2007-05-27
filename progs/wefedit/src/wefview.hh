/*
** wefview.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Sun May 27 14:50:26 2007 Nahlwe
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

#ifndef   	WEFVIEW_HH_
# define   	WEFVIEW_HH_

#include <gtkmm.h>
#include <wef.hh>

class WefView : public Gtk::DrawingArea
{
public:
  WefView(Wef &a_wef);

protected:
  virtual bool on_expose_event(GdkEventExpose* event);

  Wef                           &m_wef;

};

#endif	    /* !WEFVIEW_HH_ */
