/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is
 * Christopher Blizzard. Portions created by Christopher Blizzard are Copyright (C) Christopher Blizzard.  All Rights Reserved.
 * Portions created by the Initial Developer are Copyright (C) 2001
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Christopher Blizzard <blizzard@mozilla.org>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#include <gtkmm.h>
#include "../src/thc.h"

Thc::Slider *slider, *slider2;


void normal_mode() {
  slider->set_mode(Thc::ModeNormal);
  slider2->set_mode(Thc::ModeNormal);
}

void connect_mode() {
  slider->set_mode(Thc::ModeConnect);
  slider2->set_mode(Thc::ModeConnect);
}

  
int main (int argc, char *argv[]) {  
  Gtk::Main gtkmain (argc, argv);
  Gtk::Window window;
  Gtk::Button btn_normal("Normal");
  Gtk::Button btn_connect("Connect");
  Gtk::VBox vbox;
  Gtk::HBox hbox;
  
  slider = new Thc::Slider();
  slider2 = new Thc::Slider(Thc::Skin::create_images("../skins/bang/fader-%i.png", 127), Thc::Param::create_param(), false);
  //slider3 = new Thc::Slider(0, 0, 100, false, false, false);
  window.add(vbox);
  vbox.pack_start(hbox);
  hbox.pack_start(btn_normal);
  hbox.pack_start(btn_connect);
  vbox.pack_start(*slider);
  vbox.pack_start(*slider2);
  
  btn_connect.signal_clicked().connect(sigc::ptr_fun(&connect_mode));
  btn_normal.signal_clicked().connect(sigc::ptr_fun(&normal_mode));
    
  window.show_all();
  gtkmain.run (window);
  return 0;
}


