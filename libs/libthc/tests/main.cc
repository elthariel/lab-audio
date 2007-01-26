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
#include <sndfile.h>
#include <iostream>
#include "back-lol.xpm"
using namespace std;
using namespace Gtk;
using namespace Gdk;
using namespace Glib;
using namespace Thc;
Slider *slider;


void normal_mode() {
  ModeManager::instance()->set_mode("test", ModeNormal);
}

void connect_mode() {
  ModeManager::instance()->set_mode("test", ModeConnect);
}

void normal2_mode() {
  slider->set_skin(SkinManager::get_skin("slider/crossfader-handle-v"));
}

void connect2_mode() {
  slider->set_skin(SkinManager::get_skin("slider/crossfader-handle-h"));
}

void vector_mode() {
  slider->set_skin(SkinManager::get_skin("slider/crossfader-vector-v"));
}


int main (int argc, char *argv[]) {
  Gtk::Main gtkmain (argc, argv);

  ModeManager::instanciate();
 // SkinManager::instance()->add_path("../skins");
  SkinManager::instance()->load_all_skins();
  //SkinManager::instance()->load_skin("../skins/ctaf-skin.xml");

  Gtk::Window window;
  Gtk::Button btn_normal("Normal");
  Gtk::Button btn_connect("Connect");
  Gtk::Button btn_normal2("Skin All h");
  Gtk::Button btn_connect2("Skin All v");
  Gtk::Button btn_normal3("Skin Vect");

  Gtk::VBox vbox;
  Gtk::HBox hbox;
  Gtk::HBox hbox2;

  Slider slider2(Images::create_images("../skins/bang/fader-%i.png", 127), Param::create_param(), false, true);
  Slider slider3(Images::create_images("../skins/mixxx/poti_%i.png", 12), Param::create_param(), true);
  Slider slider4(Images::create_images("../skins/mixxx/vu%il.png", 32), Param::create_param(), false, true);
  Slider slider5(Images::create_images("../skins/mixxx/vu%ir.png", 32), Param::create_param(), false);
  Slider slider6(Param::create_param(), false);
  Slider slider7(Thc::Image::create_image("../skins/mixxx/slider_back_horiz.png"),
  				       Thc::Image::create_image("../skins/mixxx/slider_handle_horiz.png"),
  				       Param::create_param(),
  				       Slider::SliderHandle,
  				       true,
  				       false);
  Slider slider8(Thc::Image::create_image("../skins/mixxx/slider_back_vert.png"),
  				       Thc::Image::create_image("../skins/mixxx/slider_handle_vert.png"),
  				       Param::create_param(),
  				       Slider::SliderHandle,
  				       false,
  				       true);
  Slider slider9(SkinManager::get_skin("slider/crossfader-full"));
  Slider slider10(SkinManager::get_skin("slider/fader-h"));
  Slider slider11(SkinManager::get_skin("slider/fader-v"));
  slider = new Slider();
  ModeManager::instance()->add_widget("test", slider);
  delete slider;
  slider = new Slider(Param::create_param(), false, false, false);

  Gtk::Fixed m_fixed;
	m_fixed.set_has_window(true);
	RefPtr<Pixbuf> back = Pixbuf::create_from_xpm_data(back_lol_xpm);
	m_fixed.set_size_request(back->get_width(), back->get_height());
	RefPtr<Pixmap> pixmap = Pixmap::create(m_fixed.get_window(), back->get_width(), back->get_height());
	RefPtr<Bitmap> bitmap;
	back->render_pixmap_and_mask(pixmap, bitmap, 10);
	RefPtr<Style> s = m_fixed.get_style()->copy();
	s->set_bg_pixmap(STATE_NORMAL, pixmap);
	s->set_bg_pixmap(STATE_ACTIVE, pixmap);
	s->set_bg_pixmap(STATE_PRELIGHT, pixmap);
	s->set_bg_pixmap(STATE_SELECTED, pixmap);
	s->set_bg_pixmap(STATE_INSENSITIVE, pixmap);
	m_fixed.set_style(s);


  ModeManager::instance()->add_widget("test", slider);
  ModeManager::instance()->add_widget("test", slider2);
  ModeManager::instance()->add_widget("test", slider3);
  ModeManager::instance()->add_widget("test2", slider4);
  ModeManager::instance()->add_widget("test2", slider5);
  ModeManager::instance()->add_widget("test2", slider6);
  ModeManager::instance()->add_widget("test2", slider7);
  ModeManager::instance()->add_widget("test2", slider8);
  ModeManager::instance()->add_widget("test2", slider9);

  window.add(m_fixed);
  m_fixed.put(vbox, 300, 0);
  vbox.pack_start(hbox);
  //hbox.pack_start(btn_loadsample);
  hbox.pack_start(btn_normal);
  hbox.pack_start(btn_connect);
  hbox.pack_start(btn_normal2);
  hbox.pack_start(btn_connect2);
  hbox.pack_start(btn_normal3);
  vbox.pack_start(hbox2);
  hbox2.pack_start(*slider);
  hbox2.pack_start(slider2);
  hbox2.pack_start(slider3);
  hbox2.pack_start(slider4);
  hbox2.pack_start(slider5);
  hbox2.pack_start(slider7);
  hbox2.pack_start(slider8);
  hbox2.pack_start(slider9);
	m_fixed.put(slider6, 0, 0);
	m_fixed.put(slider11, 100, 0);
	m_fixed.put(slider10, 200, 0);

  btn_connect.signal_clicked().connect(sigc::ptr_fun(&connect_mode));
  btn_normal.signal_clicked().connect(sigc::ptr_fun(&normal_mode));
  btn_connect2.signal_clicked().connect(sigc::ptr_fun(&connect2_mode));
  btn_normal2.signal_clicked().connect(sigc::ptr_fun(&normal2_mode));
  btn_normal3.signal_clicked().connect(sigc::ptr_fun(&vector_mode));

  window.show_all();
  gtkmain.run (window);
  delete slider;
  return 0;
}


