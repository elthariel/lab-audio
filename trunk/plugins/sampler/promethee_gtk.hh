/*
** promethee_gtk.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Fri Jan 19 05:45:33 2007 Nahlwe
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

#ifndef   	PROMETHEE_GTK_HH_
# define   	PROMETHEE_GTK_HH_

#include <gtkmm.h>

#include "lv2gtk2gui.hpp"
#include "promethee.peg"

#define                 SAMPLES_COUNT 8

enum sedit_vbox {
  sedit_load,
  sedit_main,
  sedit_func,
  sedit_env,
  sedit_smp,
  sedit_n_hbox
};


class SampleEdit : public Gtk::VBox
{
public:
  SampleEdit(LV2Controller& ctrl, unsigned int sample_id = 0);

  bool                  set_vol(Gtk::ScrollType, double);
  bool                  set_pan(Gtk::ScrollType, double);
  bool                  set_pitch(Gtk::ScrollType, double);
  bool                  set_root(Gtk::ScrollType, double);

  void                  choose_sample();
protected:
  LV2Controller&        m_ctrl;
  unsigned int          m_sample_id;

  Gtk::HBox             m_hbox[sedit_n_hbox];
  Gtk::VBox             m_vbox_main[4];
  Gtk::Label            m_lbl_main[4];
  Gtk::Adjustment       m_main_adj_vol;
  Gtk::Adjustment       m_main_adj_pan;
  Gtk::Adjustment       m_main_adj_pitch;
  Gtk::Adjustment       m_main_adj_root;
  Gtk::VScale           m_main_scale_vol;
  Gtk::VScale           m_main_scale_pan;
  Gtk::VScale           m_main_scale_pitch;
  Gtk::VScale           m_main_scale_root;

  Gtk::Label            m_sample_path;
  Gtk::Button           m_choose_sample;

  void                  set_sample_id(unsigned int);
  void                  on_drop_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context,
                                                   int,
                                                   int,
                                                   const Gtk::SelectionData& selection_data,
                                                   guint,
                                                   guint time);
};

class PrometheeGUI : public LV2GTK2GUI
{
public:
  PrometheeGUI(LV2Controller& ctrl,
               const std::string& URI,
               const std::string& bundle_path,
               Gtk::Widget*& widget);


protected:
  LV2Controller         &m_ctrl;

  Gtk::Notebook         m_smp_notebook;
  std::vector<SampleEdit *> m_smp_edit;
  //  Label             m_smp_label[SAMPLES_COUNT];
};


#endif	    /* !PROMETHEE_GTK_HH_ */
