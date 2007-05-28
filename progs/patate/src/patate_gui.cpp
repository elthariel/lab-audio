/*
** patate_gui.cpp
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

#include <iostream>
#include <cstdio>
#include "patate_gui.hh"

using namespace std;
using namespace sigc;

PatateGUI::PatateGUI(LFRingBufferReader<Event> *a_reader,
                     LFRingBufferWriter<Event> *a_writer,
                     Patate &a_patate)
  : m_reader(a_reader),
    m_writer(a_writer),
    m_patate(a_patate),
    m_lv2(a_patate),
    m_bpm(160)
{
  unsigned int i;

  add(m_main_vbox);
  m_main_vbox.pack_start(m_main_hbox[0]);
  m_transport[0].set_label("Play");
  m_transport[1].set_label("Pause");
  m_transport[2].set_label("Stop");
  m_transport[3].set_label("Rewind");
  m_transport[4].set_label("prec");
  m_transport[5].set_label("next");
  for (i = 0; i < 6; i++)
    {
      m_main_hbox[0].pack_start(m_transport[i]);
      m_transport[i].signal_clicked()
        .connect(bind<0>(bind<1>(mem_fun(*this, &PatateGUI::event_note),
                         true),i));
    }

  set_bpmview(0);
  m_main_hbox[0].pack_start(m_bpmview);

  m_bpmedit[0].set_label("bpm - 10");
  m_bpmedit[1].set_label("bpm + 10");
  m_bpmedit[2].set_label("bpm - 1");
  m_bpmedit[3].set_label("bpm + 1");
  m_bpmedit[0].signal_clicked()
    .connect(bind<0>(bind<1>(mem_fun(*this, &PatateGUI::event_note_tempo),
                             -10),6));
  m_bpmedit[1].signal_clicked()
    .connect(bind<0>(bind<1>(mem_fun(*this, &PatateGUI::event_note_tempo),
                             +10),7));
  m_bpmedit[2].signal_clicked()
    .connect(bind<0>(bind<1>(mem_fun(*this, &PatateGUI::event_note_tempo),
                             -1),8));
  m_bpmedit[3].signal_clicked()
    .connect(bind<0>(bind<1>(mem_fun(*this, &PatateGUI::event_note_tempo),
                             +1),9));
  for(i = 0; i < 4; i++)
      m_main_hbox[0].pack_start(m_bpmedit[i]);

  for (i = 0; i < 16; i++)
    {
      m_seqview[i] = new DrumSeqView(*this, i);
      m_main_vbox.pack_end(*m_seqview[i]);
      m_synthviews[i] = new GenericSynthView(*this, i);
      m_seqview[i]->pack_end(*m_synthviews[i]);
    }
  show_all();


  /*
   * Test code
   */
  Lv2Adapter *synth;
  for (i = 0; i < 16; i++)
    {
      synth = m_lv2.make_lv2(4); // Change here to load another synth.
      if (synth)
        m_patate.get_synths().synth(i, *synth);
      else
        cout << "Unable to load synth" << endl;
    }
}

PatateGUI::~PatateGUI()
{
}

void            PatateGUI::gui_update()
{
  Event         ev;

  if (m_reader->ready())
    {
      m_reader->read(&ev);
      process_gui_event(ev);
    }
}

void            PatateGUI::process_gui_event(Event &a_ev)
{
}

LFRingBufferReader<Event>     *PatateGUI::reader()
{
  return m_reader;
}

LFRingBufferWriter<Event>     *PatateGUI::writer()
{
  return m_writer;
}

void            PatateGUI::event_note(char note, bool on)
{
  Event         ev;

  ev.subsystem = Sys_Main;
  ev.type = Event::TypeNote;
  ev.data.note.on = true;
  ev.data.note.note = note;
  ev.data.note.vel = 127;
  if (m_writer->ready())
    m_writer->write(&ev);
}

void            PatateGUI::event_note_tempo(char note, int offset)
{
  set_bpmview(offset);
  event_note(note);
}

void            PatateGUI::set_bpmview(int offset)
{
  char          tmp[6];

  if ((offset < 0) && ((m_bpm + offset) <= 0))
    return;
  m_bpm += offset;
  snprintf((char *)tmp, 6, "%d", m_bpm);
  m_bpmview.set_label((char *)tmp);
}
