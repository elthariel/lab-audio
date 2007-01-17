/*
** main.cc
** Login : <elthariel@elthariel-desktop>
** Started on  Tue Jan 16 03:09:42 2007 Nahlwe
** $Id$
**
** Copyright (C) 2007 Nahlwe
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#include <iostream>
#include <string>
//#include <gtkmm.h>
#include "WaView.hh"
#include <sndfile.h>

int             main(int ac, char **av)
{
  Gtk::Main     kit(ac, av);

  Gtk::Window   win;
  WaView        view;

  win.set_title("WaView test program");
  win.add(view);

  Gtk::FileChooserDialog dialog("Choose a sample",
                                Gtk::FILE_CHOOSER_ACTION_OPEN);
  //dialog.set_transient_for(win);

  //Add response buttons the the dialog:
  dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

  Gtk::FileFilter filter_samples;
  filter_samples.set_name("Audio sample Files");
  filter_samples.add_pattern("*.wav");
  filter_samples.add_pattern("*.aiff");
  dialog.add_filter(filter_samples);

  int result = dialog.run();

  //Handle the response:
  switch(result)
  {
    case(Gtk::RESPONSE_OK):
    {
      SF_INFO           sfinfo;
      SNDFILE           *sndf;
      sample_t          *samples;

      std::cout << "Open clicked." << std::endl;
      std::string filename = dialog.get_filename();
      std::cout << "File selected: " <<  filename << std::endl;

      sndf = sf_open(filename.c_str(), SFM_READ, &sfinfo);
      if (sndf)
        {
          samples = new sample_t[sfinfo.frames];
          sf_readf_float(sndf, samples, sfinfo.frames);
          view.set_data(samples, sfinfo.frames, sfinfo.channels);


          win.show_all();
          Gtk::Main::run(win);
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
