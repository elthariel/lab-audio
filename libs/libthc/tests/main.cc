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

using namespace Thc;

void normal_mode() {
  ModeManager::instance()->set_mode("test", ModeNormal);
}

void connect_mode() {
  ModeManager::instance()->set_mode("test", ModeConnect);
}

void normal2_mode() {
  ModeManager::instance()->set_mode("test2", ModeNormal);
}

void connect2_mode() {
  ModeManager::instance()->set_mode("test2", ModeConnect);
}
  
int main (int argc, char *argv[]) {  
  Gtk::Main gtkmain (argc, argv);
  Gtk::Window window;
  Gtk::Button btn_normal("Normal");
  Gtk::Button btn_connect("Connect");
  Gtk::Button btn_normal2("Normal2");
  Gtk::Button btn_connect2("Connect2");
  Gtk::VBox vbox;
  Gtk::HBox hbox;
  Gtk::HBox hbox2;
  Slider *slider;
  Slider slider2(Thc::Images::create_images("../skins/bang/fader-%i.png", 127), Param::create_param(), false, true);
  Slider slider3(Thc::Images::create_images("../skins/mixxx/poti_%i.png", 12), Param::create_param(), true);
  Slider slider4(Thc::Images::create_images("../skins/mixxx/vu%il.png", 32), Param::create_param(), false, true);
  Slider slider5(Thc::Images::create_images("../skins/mixxx/vu%ir.png", 32), Param::create_param(), false);
  Slider slider6(Param::create_param(), false);
  Slider slider7(Thc::Image::create_image("../skins/mixxx/slider_back_horiz.png"),
  				 Thc::Image::create_image("../skins/mixxx/slider_handle_horiz.png"),
  				 Param::create_param(), Thc::Slider::SliderHandle, true, false);
  Slider slider8(Thc::Image::create_image("../skins/mixxx/slider_back_vert.png"),
  				 Thc::Image::create_image("../skins/mixxx/slider_handle_vert.png"),
  				 Param::create_param(), Thc::Slider::SliderHandle, false, true);

  
  SkinManager::instanciate();
  ModeManager::instanciate();
  
  slider = new Slider();
  ModeManager::instance()->add_widget("test", slider);
  delete slider;
  slider = new Slider();
  
  ModeManager::instance()->add_widget("test", slider);
  ModeManager::instance()->add_widget("test", slider2);
  ModeManager::instance()->add_widget("test", slider3);
  ModeManager::instance()->add_widget("test2", slider4);
  ModeManager::instance()->add_widget("test2", slider5);
  ModeManager::instance()->add_widget("test2", slider6);
  ModeManager::instance()->add_widget("test2", slider7);
  ModeManager::instance()->add_widget("test2", slider8);
  
  window.add(vbox);
  vbox.pack_start(hbox);
  hbox.pack_start(btn_normal);
  hbox.pack_start(btn_connect);
  hbox.pack_start(btn_normal2);
  hbox.pack_start(btn_connect2);
  vbox.pack_start(hbox2);
  hbox2.pack_start(*slider);
  hbox2.pack_start(slider2);
  hbox2.pack_start(slider3);
  hbox2.pack_start(slider4);
  hbox2.pack_start(slider5);
  hbox2.pack_start(slider6);
  hbox2.pack_start(slider7);
  hbox2.pack_start(slider8);
  
  btn_connect.signal_clicked().connect(sigc::ptr_fun(&connect_mode));
  btn_normal.signal_clicked().connect(sigc::ptr_fun(&normal_mode));
  btn_connect2.signal_clicked().connect(sigc::ptr_fun(&connect2_mode));
  btn_normal2.signal_clicked().connect(sigc::ptr_fun(&normal2_mode));
    
  window.show_all();
  gtkmain.run (window);
  delete slider;
  return 0;
}


