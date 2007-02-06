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

class FilterEdit : public Gtk::VBox
{
public:
  FilterEdit(LV2Controller& ctrl, unsigned int sample_id);

  class TMFtype : public Gtk::TreeModel::ColumnRecord
  {
  public:
    TMFtype();
    Gtk::TreeModelColumn<Glib::ustring>   m_col_ftype;
    Gtk::TreeModelColumn<int>             m_col_ftype_id;
  };
  class TMFStage : public Gtk::TreeModel::ColumnRecord
  {
  public:
    TMFStage();
    Gtk::TreeModelColumn<int>             m_col_stage;
  };

private:
  LV2Controller         &m_ctrl;
  unsigned int          m_sample_id;
  unsigned int          m_pcount;
  Glib::RefPtr<Gtk::ListStore> m_ftype_model;
  Glib::RefPtr<Gtk::ListStore> m_fstages_model;
  TMFtype               m_tmftype;
  TMFStage              m_tmfstage;

  Gtk::HBox             m_box_ftype;
  Gtk::HBox             m_box_param;
  Gtk::Label            m_lb_ftype;
  Gtk::ComboBox         m_cb_ftype;
  Gtk::Label            m_lb_fstages;
  Gtk::ComboBox         m_cb_fstages;
  Gtk::Adjustment       m_ad_fcut;
  Gtk::Adjustment       m_ad_fres;
  Gtk::VScale           m_vs_fcut;
  Gtk::VScale           m_vs_fres;

};

class EnvEdit : public Gtk::VBox
{
public:
  EnvEdit(LV2Controller& ctrl, unsigned int sample_id,
          unsigned int base_peg, bool amount = true);

protected:
  void                  bind_scale(Gtk::Adjustment &,
                                   unsigned int port);
  void                  bind_radio(Gtk::RadioButton &,
                                   int but_num,
                                   unsigned int port);
  void                  radio_check(unsigned int port,
                                    int button,
                                    bool val);

  LV2Controller         &m_ctrl;

  Gtk::HBox             m_hbox;
  Gtk::HBox             m_env_hbox;
  Gtk::Adjustment       m_amount;
  Gtk::Adjustment       m_coef0;
  Gtk::Adjustment       m_coef1;
  Gtk::Adjustment       m_coef2;
  Gtk::Adjustment       m_coef3;
  Gtk::Adjustment       m_coef4;
  Gtk::Adjustment       m_coef5;
  Gtk::VScale           m_scale_amount;
  Gtk::VScale           m_scale0;
  Gtk::VScale           m_scale1;
  Gtk::VScale           m_scale2;
  Gtk::VScale           m_scale3;
  Gtk::VScale           m_scale4;
  Gtk::VScale           m_scale5;
  Gtk::RadioButton::Group m_env_select;
  Gtk::RadioButton      m_env_none;
  Gtk::RadioButton      m_env_decay;
  Gtk::RadioButton      m_env_hold;
  Gtk::RadioButton      m_env_dahdsr;
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
  unsigned int          m_pcount; //port count

  Gtk::VBox             m_nonrt_vbox;
  Gtk::CheckButton      m_rev;
  Gtk::CheckButton      m_norm;
  Gtk::CheckButton      m_aalias;

  EnvEdit               m_amp_env;
  EnvEdit               m_pan_env;
  EnvEdit               m_pitch_env;
  EnvEdit               m_fcut_env;
  EnvEdit               m_fres_env;
  Gtk::Notebook         m_env_notebook;
  FilterEdit            m_fedit;

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
