//
// atropos_gtk.cpp for atropos in /home/elthariel/code/lab-audio/plugins/atropos
//
// Copyright 2007 Elthariel
// Login   <elthariel@lse.epita.fr>
//
// Started on  Thu Feb  8 00:30:28 2007 Nahlwe
// Last update Fri Feb  9 13:10:36 2007 Nahlwe
//

#include <iostream>
#include "atropos_gtk.hpp"
#include "atropos.peg"

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
 * MixSlice class
 */
MixSlice::MixSlice(LV2Controller &ctrl,
           unsigned int track_id)
  : m_ctrl(ctrl), m_id(track_id),
    m_pcount(peg_eq_crossover1_0 - peg_volume_0 + 1)
{
  unsigned int          i;

  for (i = 0; i < sl_count; i++)
    m_params[i] = create_param();

  m_slider[sl_vol] = new Slider(SkinManager::get_skin("slider/fader"),
                                m_params[sl_vol], true);
  m_slider[sl_vol]->set_size_request(50, 130);
  pack_end(*(m_slider[sl_vol]));
  for (i = sl_send1; i < sl_count; i++)
    {
      m_slider[i] = new Slider(SkinManager::get_skin("slider/rotary"),
                               m_params[i], true);
      m_slider[i]->set_size_request(50, 50);
      pack_end(*(m_slider[i]));
    }

  m_params[0]->signal_value_changed().
    connect(compose(bind<0>(mem_fun(*this, &MixSlice::change_scale),
                            peg_volume_0),
                    mem_fun(*(m_params[0].get()), &Param::get_value)));
  m_params[1]->signal_value_changed().
    connect(compose(bind<0>(mem_fun(*this, &MixSlice::change_scale),
                            peg_send_fx0_0),
                    mem_fun(*(m_params[1]), &Param::get_value)));
  m_params[2]->signal_value_changed().
    connect(compose(bind<0>(mem_fun(*this, &MixSlice::change_scale),
                            peg_send_fx1_0),
                    mem_fun(*(m_params[2]), &Param::get_value)));
  m_params[3]->signal_value_changed().
    connect(compose(bind<0>(mem_fun(*this, &MixSlice::change_scale),
                            peg_send_fx2_0),
                    mem_fun(*(m_params[3]), &Param::get_value)));
  m_params[4]->signal_value_changed().
    connect(compose(bind<0>(mem_fun(*this, &MixSlice::change_scale),
                            peg_send_fx3_0),
                    mem_fun(*(m_params[4]), &Param::get_value)));
}

void            MixSlice::change_scale(unsigned int base_port,
                                       float val)
{
  m_ctrl.set_control(base_port + m_id * m_pcount, dB2rap(val));
}

/*
 * AtroposGUI class
 */

AtroposGUI::AtroposGUI(LV2Controller& ctrl,
                       const std::string& URI,
                       const std::string& bundle_path,
                       Widget*& widget)
  : m_ctrl(ctrl)
{
  unsigned int  i;
  MixSlice      *tmp;

  widget = &m_hbox;

  for (i = 0; i < TRACK_COUNT; i++)
    {
      tmp = new MixSlice(m_ctrl, i);
      m_hbox.pack_start(*tmp);
    }
  m_hbox.pack_start(m_vbox_main);
}

void initialise() __attribute__((constructor));
void initialise() {
  register_lv2gtk2gui<AtroposGUI>(peg_uri);
}
