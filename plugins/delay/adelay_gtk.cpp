//
// atropos_gtk.cpp for atropos in /home/elthariel/code/lab-audio/plugins/atropos
//
// Copyright 2007 Elthariel
// Login   <elthariel@lse.epita.fr>
//
// Started on  Thu Feb  8 00:30:28 2007 Nahlwe
// Last update Tue Feb 13 08:16:03 2007 Nahlwe
//

#include <iostream>
#include "adelay_gtk.hpp"
#include "adelay.peg"

using namespace std;
using namespace Gtk;
using namespace sigc;
using namespace Thc;

Param::Ref create_param(int port) {
  return Param::create_param(peg_ports[port].min,
                             peg_ports[port].max,
                             peg_ports[port].default_value);
}

Adjustment *create_adj(int port) {
  return new Adjustment(peg_ports[port].default_value,
                        peg_ports[port].min,
                        peg_ports[port].max);
}

Param::Ref create_param() {
  return Param::create_param(-40., 12., 0.);
}

/*
 * ADelayGUI class
 */

ADelayGUI::ADelayGUI(LV2Controller& ctrl,
                     const std::string& URI,
                     const std::string& bundle_path,
                     Widget*& widget)
  : m_ctrl(ctrl),
    m_time_sw("Beats")
{
  unsigned int i;

  widget = &m_hbox;

  // Tempo spinbutton
  m_labels[0].set_label("Tempo");
  m_hbox.pack_start(m_labels[0]);
  m_adjs[0] = create_adj(peg_tempo);
  m_spins[0] = new SpinButton(*(m_adjs[0]));
  m_adjs[0]->signal_value_changed().
    connect(compose(bind<0>(mem_fun(m_ctrl, &LV2Controller::set_control),
                            peg_tempo),
                    mem_fun(*(m_adjs[0]), &Adjustment::get_value)));
  m_hbox.pack_start(*m_spins[0]);

  // Time source swith
  m_labels[1].set_label("Delay time\nsource switch");
  m_hbox.pack_start(m_labels[1]);
  m_time_sw.signal_toggled().
    connect(compose(bind<0>(mem_fun(m_ctrl, &LV2Controller::set_control),
                            peg_time_sw),
                    mem_fun(m_time_sw, &ToggleButton::get_active)));
  m_hbox.pack_start(m_time_sw);

  // Time_ms
  m_labels[2].set_label("ms");
  m_hbox.pack_start(m_labels[2]);
  m_adjs[1] = create_adj(peg_tempo);
  m_spins[1] = new SpinButton(*(m_adjs[1]));
  m_adjs[1]->signal_value_changed().
    connect(compose(bind<0>(mem_fun(m_ctrl, &LV2Controller::set_control),
                            peg_time_ms),
                    mem_fun(*(m_adjs[1]), &Adjustment::get_value)));
  m_hbox.pack_start(*m_spins[1]);

  // Time beat
  m_labels[3].set_label("beats");
  m_hbox.pack_start(m_labels[3]);
  m_adjs[2] = create_adj(peg_time_beat);
  m_spins[2] = new SpinButton(*(m_adjs[2]));
  m_adjs[2]->signal_value_changed().
    connect(compose(bind<0>(mem_fun(m_ctrl, &LV2Controller::set_control),
                            peg_time_beat),
                    mem_fun(*(m_adjs[2]), &Adjustment::get_value)));
  m_hbox.pack_start(*m_spins[2]);

  // Feedback
  m_labels[4].set_label("Feedback");
  m_hbox.pack_start(m_labels[4]);
  m_params[0] = create_param(peg_feedback);
  m_sliders[0] = new Slider(SkinManager::get_skin("slider/rotary"),
                            m_params[0], true);
  m_sliders[0]->set_size_request(40, 40);
  m_hbox.pack_start(*(m_sliders[0]));
  m_params[0]->signal_value_changed().
    connect(compose(bind<0>(mem_fun(m_ctrl, &LV2Controller::set_control),
                            peg_feedback),
                    mem_fun(*(m_params[0]), &Param::get_value)));

  // Amount
  m_labels[5].set_label("Dry/Wet");
  m_hbox.pack_start(m_labels[5]);
  m_params[1] = create_param(peg_feedback);
  m_sliders[1] = new Slider(SkinManager::get_skin("slider/rotary"),
                            m_params[1], true);
  m_sliders[1]->set_size_request(40, 40);
  m_hbox.pack_start(*(m_sliders[1]));
  m_params[1]->signal_value_changed().
    connect(compose(bind<0>(mem_fun(m_ctrl, &LV2Controller::set_control),
                            peg_amount),
                    mem_fun(*(m_params[1]), &Param::get_value)));

  //   m_labels[0].set_use_markup();
  //   m_labels[0].
  //     set_markup("<span background=\"black\" foreground=\"white\">Pitch</span>");
  //   m_params[0]->signal_value_changed().
  //     connect(compose(bind<0>(mem_fun(m_ctrl, &LV2Controller::set_control),
  //                             peg_pitch),
  //                     mem_fun(*(m_params[0]), &Param::get_value)));
}

void initialise() __attribute__((constructor));
void initialise() {
  register_lv2gtk2gui<ADelayGUI>(peg_uri);
}
