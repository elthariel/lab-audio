/*
** drumseqview.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Wed Apr 11 14:37:30 2007 Nahlwe
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

#ifndef   	DRUMSEQVIEW_HH_
# define   	DRUMSEQVIEW_HH_

#include <gtkmm.h>
#include <vector>
#include "sampler.hh"
#include "seq.hh"
#include "patate.hh"

class PatateGUI;

class DrumSeqView : public Gtk::VBox
{
public:
  DrumSeqView(PatateGUI &a_gui,
              unsigned int a_init_track);
protected:
  void                  step_pressed(unsigned int a_step_id);

  PatateGUI             &m_gui;
  unsigned int          m_track_id;
  Gtk::HBox             m_seq_hbox;
  Gtk::ToggleButton     m_steps[16];
};

#include "patate_gui.hh"

#endif	    /* !DRUMSEQVIEW_HH_ */
