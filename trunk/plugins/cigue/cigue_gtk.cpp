//
// atropos_gtk.cpp for atropos in /home/elthariel/code/lab-audio/plugins/atropos
//
// Copyright 2007 Elthariel
// Login   <elthariel@lse.epita.fr>
//
// Started on  Thu Feb  8 00:30:28 2007 Nahlwe
// Last update Sat Feb 10 05:40:18 2007 Nahlwe
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
  widget = &m_hbox;
}

void initialise() __attribute__((constructor));
void initialise() {
  register_lv2gtk2gui<CigueGUI>(peg_uri);
}
