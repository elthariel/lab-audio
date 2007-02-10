//
// atropos_gtk.cpp for atropos in /home/elthariel/code/lab-audio/plugins/atropos
//
// Copyright 2007 Elthariel
// Login   <elthariel@lse.epita.fr>
//
// Started on  Thu Feb  8 00:30:28 2007 Nahlwe
// Last update Sat Feb 10 10:52:48 2007 Nahlwe
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

  m_labels[0].set_label("Pitch");
  m_labels[1].set_label("Cut");
  m_labels[2].set_label("Res");
  m_labels[3].set_label("EnvMod");
  m_labels[4].set_label("Decay");
  m_labels[5].set_label("Glide");
  for (i = 0; i < 6; i++)
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

}

void initialise() __attribute__((constructor));
void initialise() {
  register_lv2gtk2gui<CigueGUI>(peg_uri);
}
