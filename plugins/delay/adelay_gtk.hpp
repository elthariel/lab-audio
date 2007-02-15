//
// atropos_gtk.hpp for atropos in /home/elthariel/code/lab-audio/plugins/atropos
//
// Copyright 2007 Elthariel
// Login   <elthariel@lse.epita.fr>
//
// Started on  Thu Feb  8 00:30:28 2007 Nahlwe
// Last update Tue Feb 13 08:01:59 2007 Nahlwe
//

#ifndef ATROPOS_GTK_HPP_
# define ATROPOS_GTK_HPP_

# include <gtkmm.h>
# include <thc/thc.h>
# include <thc/skinmanager.h>
# include "adelay_gtk.hpp"
# include "lv2gtk2gui.hpp"
# include <cmath>

class ADelayGUI : public LV2GTK2GUI
{
public:
  ADelayGUI(LV2Controller &ctrl,
             const std::string &URI,
             const std::string &bundle_path,
             Gtk::Widget *&widget);

protected:
  LV2Controller         &m_ctrl;

  Gtk::HBox             m_hbox;
  Thc::Slider           *m_sliders[2]; //feedback, amount
  Thc::Param::Ref       m_params[2];
  Gtk::Label            m_labels[6];
  Gtk::ToggleButton     m_time_sw;
  Gtk::SpinButton       *m_spins[3]; //tempo, beat, ms
  Gtk::Adjustment       *m_adjs[3];
};

#endif
