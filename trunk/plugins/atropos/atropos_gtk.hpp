//
// atropos_gtk.hpp for atropos in /home/elthariel/code/lab-audio/plugins/atropos
//
// Copyright 2007 Elthariel
// Login   <elthariel@lse.epita.fr>
//
// Started on  Thu Feb  8 00:30:28 2007 Nahlwe
// Last update Fri Feb  9 09:49:16 2007 Nahlwe
//

#ifndef ATROPOS_GTK_HPP_
# define ATROPOS_GTK_HPP_

# include <gtkmm.h>
# include <thc/thc.h>
# include <thc/skinmanager.h>
# include "atropos_gtk.hpp"
# include "lv2gtk2gui.hpp"
# include <cmath>

# define LOG_10 2.302585093
# define dB2rap(dB) ((exp((dB)*LOG_10/20.0)))
# define rap2dB(rap) ((20*log(rap)/LOG_10))

# define TRACK_COUNT    16

enum e_mixslice
  {
    sl_vol,
    sl_send1,
    sl_send2,
    sl_send3,
    sl_send4,
    sl_count
  };

class MixSlice : public Gtk::VBox
{
public:
  MixSlice(LV2Controller &ctrl,
           unsigned int track_id);

protected:
  void                  change_scale(unsigned int base_port,
                                     float val);

  LV2Controller         &m_ctrl;
  unsigned int          m_id;
  unsigned int          m_pcount;

  Thc::Slider           *m_slider[sl_count];
  Thc::Param::Ref       m_params[sl_count];
};

class AtroposGUI : public LV2GTK2GUI
{
public:
  AtroposGUI(LV2Controller &ctrl,
             const std::string &URI,
             const std::string &bundle_path,
             Gtk::Widget *&widget);

protected:
  LV2Controller         &m_ctrl;

  Gtk::HBox             m_hbox;
  Gtk::VBox             m_vbox_main;
  Gtk::Adjustment       *m_adj[sl_count];
  Gtk::VScale           *m_va[sl_count];
  MixSlice              *m_slices[TRACK_COUNT];
};

#endif
