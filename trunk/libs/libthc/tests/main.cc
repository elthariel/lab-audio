/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */


//
// Class: Main
//
// Created by: GESTES Cedric <goctaf@gmail.com>
// Created on: Sun Dec  3 19:34:17 2006
//

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
  
  SkinManager::instanciate();
  ModeManager::instanciate();
  SkinManager::instance()->load_path("../skins");
  //SkinManager::instance()->load_skin("../skins/ctaf-skin.xml");

  Gtk::Window window;
  Gtk::Button btn_normal("Normal");
  Gtk::Button btn_connect("Connect");
  Gtk::Button btn_normal2("Normal2");
  Gtk::Button btn_connect2("Connect2");
  Gtk::VBox vbox;
  Gtk::HBox hbox;
  Gtk::HBox hbox2;
  Slider *slider;
  Slider slider2(Images::create_images("../skins/bang/fader-%i.png", 127), Param::create_param(), false, true);
  Slider slider3(Images::create_images("../skins/mixxx/poti_%i.png", 12), Param::create_param(), true);
  Slider slider4(Images::create_images("../skins/mixxx/vu%il.png", 32), Param::create_param(), false, true);
  Slider slider5(Images::create_images("../skins/mixxx/vu%ir.png", 32), Param::create_param(), false);
  Slider slider6(Param::create_param(), false);
  Slider slider7(Image::create_image("../skins/mixxx/slider_back_horiz.png"),
  				       Image::create_image("../skins/mixxx/slider_handle_horiz.png"),
  				       Param::create_param(),
  				       Slider::SliderHandle,
  				       true,
  				       false);
  Slider slider8(Image::create_image("../skins/mixxx/slider_back_vert.png"),
  				       Image::create_image("../skins/mixxx/slider_handle_vert.png"),
  				       Param::create_param(),
  				       Slider::SliderHandle,
  				       false,
  				       true);
  Slider slider9(SkinManager::instance()->get_skin("slider/crossfader-full"));

  
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
  ModeManager::instance()->add_widget("test2", slider9);
  
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
  hbox2.pack_start(slider9);
  
  btn_connect.signal_clicked().connect(sigc::ptr_fun(&connect_mode));
  btn_normal.signal_clicked().connect(sigc::ptr_fun(&normal_mode));
  btn_connect2.signal_clicked().connect(sigc::ptr_fun(&connect2_mode));
  btn_normal2.signal_clicked().connect(sigc::ptr_fun(&normal2_mode));
    
  window.show_all();
  gtkmain.run (window);
  delete slider;
  return 0;
}


