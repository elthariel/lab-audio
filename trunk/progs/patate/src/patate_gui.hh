/*
** patate_gui.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Tue Apr 10 02:57:27 2007 Nahlwe
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

#ifndef   	PATATE_GUI_HH_
# define   	PATATE_GUI_HH_

#include <gtkmm.h>
#include "drumseqview.hh"
#include "synthview_generic.hh"
#include "lfringbuffer.hh"
#include "event.hh"

#ifdef DRUMSEQVIEW_HH_
class DrumSeqView;
#endif

class PatateGUI : public Gtk::Window
{
public:
  PatateGUI(LFRingBufferReader<Event> *a_reader,
            LFRingBufferWriter<Event> *a_writer,
            Patate &a_patate);
  ~PatateGUI();

  LFRingBufferReader<Event>     *reader();
  LFRingBufferWriter<Event>     *writer();

protected:
  void          gui_update();
  void          process_gui_event(Event &a_ev);
  void          event_note(char note, bool on = true);
  void          event_note_tempo(char note, int offset);
  void          set_bpmview(int offset);

  LFRingBufferReader<Event>     *m_reader;
  LFRingBufferWriter<Event>     *m_writer;
  Patate                        &m_patate;
  GenericSynthView              *m_synthviews[16];
  Gtk::VBox                     m_main_vbox;
  Gtk::HBox                     m_main_hbox[4];
  Gtk::Button                   m_transport[6];
  unsigned int                  m_bpm;
  Gtk::Button                   m_bpmedit[4];
  Gtk::Label                    m_bpmview;
  DrumSeqView                   *m_seqview[16];
};

#endif	    /* !PATATE_GUI_HH_ */
