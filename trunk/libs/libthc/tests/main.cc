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
using namespace Thc;
Slider *slider;
WaveView *wview1;

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
void load_sample() {
  Gtk::FileChooserDialog dialog("Choose a sample", Gtk::FILE_CHOOSER_ACTION_OPEN);
  //dialog.set_transient_for(win);

  //Add response buttons the the dialog:
  dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

  Gtk::FileFilter filter_samples;
  filter_samples.set_name("Audio sample Files");
  filter_samples.add_pattern("*.wav");
  filter_samples.add_pattern("*.aiff");
  dialog.add_filter(filter_samples);

  std::cout << "diaglo.run" << std::endl;
  int result = dialog.run();
  std::cout << "after diaglo.run" << std::endl;

  //Handle the response:
  switch(result)
  {
    case(Gtk::RESPONSE_OK):
    {
      SF_INFO           sfinfo;
      SNDFILE           *sndf;
      WaveView::sample_t          *samples;

      std::cout << "Open clicked." << std::endl;
      std::string filename = dialog.get_filename();
      std::cout << "File selected: " <<  filename << std::endl;

      sndf = sf_open(filename.c_str(), SFM_READ, &sfinfo);
      if (sndf)
        {
          samples = new WaveView::sample_t[sfinfo.frames];
          sf_readf_float(sndf, samples, sfinfo.frames);
          wview1->set_data(samples, sfinfo.frames, sfinfo.channels);
        }
      break;
    }
    case(Gtk::RESPONSE_CANCEL):
    {
      std::cout << "Cancel clicked." << std::endl;
      break;
    }
    default:
    {
      std::cout << "Unexpected button clicked." << std::endl;
      break;
    }
  }
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
  Gtk::Button btn_normal2("Skin All h");
  Gtk::Button btn_connect2("Skin All v");
  Gtk::Button btn_normal3("Skin Vect");
  Gtk::Button btn_loadsample("Load a Sample");

  Gtk::VBox vbox;
  Gtk::HBox hbox;
  Gtk::HBox hbox2;

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
  Slider slider9(SkinManager::get_skin("slider/crossfader-full"));
  wview1 = new WaveView();
  slider = new Slider();
  ModeManager::instance()->add_widget("test", slider);
  delete slider;
  slider = new Slider(Param::create_param(), false, false, false);

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
  hbox.pack_start(btn_loadsample);
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
  hbox2.pack_start(slider6);
  hbox2.pack_start(slider7);
  hbox2.pack_start(slider8);
  hbox2.pack_start(slider9);

  btn_connect.signal_clicked().connect(sigc::ptr_fun(&connect_mode));
  btn_normal.signal_clicked().connect(sigc::ptr_fun(&normal_mode));
  btn_connect2.signal_clicked().connect(sigc::ptr_fun(&connect2_mode));
  btn_normal2.signal_clicked().connect(sigc::ptr_fun(&normal2_mode));
  btn_normal3.signal_clicked().connect(sigc::ptr_fun(&vector_mode));
  btn_loadsample.signal_clicked().connect(sigc::ptr_fun(&load_sample));

  vbox.pack_start(*wview1);

  window.show_all();
  gtkmain.run (window);
  delete slider;
  return 0;
}


