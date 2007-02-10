//
// atropos_gtk.hpp for atropos in /home/elthariel/code/lab-audio/plugins/atropos
//
// Copyright 2007 Elthariel
// Login   <elthariel@lse.epita.fr>
//
// Started on  Thu Feb  8 00:30:28 2007 Nahlwe
// Last update Sat Feb 10 05:40:19 2007 Nahlwe
//

#ifndef ATROPOS_GTK_HPP_
# define ATROPOS_GTK_HPP_

# include <gtkmm.h>
# include <thc/thc.h>
# include <thc/skinmanager.h>
# include "cigue_gtk.hpp"
# include "lv2gtk2gui.hpp"
# include <cmath>

# define LOG_10 2.302585093
# define dB2rap(dB) ((exp((dB)*LOG_10/20.0)))
# define rap2dB(rap) ((20*log(rap)/LOG_10))

class CigueGUI : public LV2GTK2GUI
{
public:
  CigueGUI(LV2Controller &ctrl,
             const std::string &URI,
             const std::string &bundle_path,
             Gtk::Widget *&widget);

protected:
  LV2Controller         &m_ctrl;

  Gtk::HBox             m_hbox;
};

#endif
