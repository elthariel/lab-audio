//
// atropos_gtk.cpp for atropos in /home/elthariel/code/lab-audio/plugins/atropos
//
// Copyright 2007 Elthariel
// Login   <elthariel@lse.epita.fr>
//
// Started on  Thu Feb  8 00:30:28 2007 Nahlwe
// Last update Mon Feb 12 02:24:04 2007 Nahlwe
//

#include <iostream>
#include "cigue_gtk.hpp"
#include "cigue.peg"

using namespace std;
using namespace Gtk;
using namespace sigc;
using namespace Thc;

Param::Ref create_param(int port) {
  return Param::create_param(peg_ports[port].min,
                             peg_ports[port].max,
                             peg_ports[port].default_value);
}

Param::Ref create_param() {
  return Param::create_param(-40., 12., 0.);
}

/*
 * CigueGUI class
 */

CigueGUI::CigueGUI(LV2Controller& ctrl,
                   const std::string& URI,
                   const std::string& bundle_path,
                   Widget*& widget)
  : m_ctrl(ctrl)
{
  unsigned int i;

  widget = &m_hbox;
  m_hbox.modify_bg(STATE_NORMAL, Gdk::Color("#000000"));

  m_labels[0].set_use_markup();
  m_labels[0].
    set_markup("<span background=\"black\" foreground=\"white\">Pitch</span>");
  m_labels[1].set_use_markup();
  m_labels[1].
    set_markup("<span background=\"black\" foreground=\"white\">Cutoff</span>");
  m_labels[2].set_use_markup();
  m_labels[2].
    set_markup("<span background=\"black\" foreground=\"white\">Res</span>");
  m_labels[3].set_use_markup();
  m_labels[3].
    set_markup("<span background=\"black\" foreground=\"white\">EnvMod</span>");
  m_labels[4].set_use_markup();
  m_labels[4].
    set_markup("<span background=\"black\" foreground=\"white\">Decay</span>");
  m_labels[5].set_use_markup();
  m_labels[5].
    set_markup("<span background=\"black\" foreground=\"white\">Glide</span>");
  m_labels[6].set_use_markup();
  m_labels[6].
    set_markup("<span background=\"black\" foreground=\"white\">Dist</span>");

  for (i = 0; i < 7; i++)
    {
      m_params[i] = create_param(peg_pitch + i);
      m_slider[i] = new Slider(SkinManager::get_skin("slider/rotary"),
                               m_params[i], true);
      m_slider[i]->set_size_request(50, 50);
      m_hbox.pack_start(m_labels[i]);
      m_hbox.pack_start(*(m_slider[i]));
    }

  m_params[0]->signal_value_changed().
    connect(compose(bind<0>(mem_fun(m_ctrl, &LV2Controller::set_control),
                            peg_pitch),
                    mem_fun(*(m_params[0]), &Param::get_value)));
  m_params[1]->signal_value_changed().
    connect(compose(bind<0>(mem_fun(m_ctrl, &LV2Controller::set_control),
                            peg_cutoff),
                    mem_fun(*(m_params[1]), &Param::get_value)));
  m_params[2]->signal_value_changed().
    connect(compose(bind<0>(mem_fun(m_ctrl, &LV2Controller::set_control),
                            peg_res),
                    mem_fun(*(m_params[2]), &Param::get_value)));
  m_params[3]->signal_value_changed().
    connect(compose(bind<0>(mem_fun(m_ctrl, &LV2Controller::set_control),
                            peg_env_mod),
                    mem_fun(*(m_params[3]), &Param::get_value)));
  m_params[4]->signal_value_changed().
    connect(compose(bind<0>(mem_fun(m_ctrl, &LV2Controller::set_control),
                            peg_env_decay),
                    mem_fun(*(m_params[4]), &Param::get_value)));
  m_params[5]->signal_value_changed().
    connect(compose(bind<0>(mem_fun(m_ctrl, &LV2Controller::set_control),
                            peg_glide),
                    mem_fun(*(m_params[5]), &Param::get_value)));
  m_params[6]->signal_value_changed().
    connect(compose(bind<0>(mem_fun(m_ctrl, &LV2Controller::set_control),
                            peg_dist),
                    mem_fun(*(m_params[6]), &Param::get_value)));
}

void initialise() __attribute__((constructor));
void initialise() {
  register_lv2gtk2gui<CigueGUI>(peg_uri);
}
