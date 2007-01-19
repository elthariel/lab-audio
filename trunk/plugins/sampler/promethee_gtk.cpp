//
// promethee_gtk.cpp for promethee in /home/elthariel/code/lab-audio/plugins/sampler
//
// Made by Elthariel
// Login   <elthariel@lse.epita.fr>
//
// Started on  Thu Jan 18 16:58:36 2007 Elthariel
// Last update Thu Jan 18 22:25:18 2007 Nahlwe
//

#include <iostream>

#include <gtkmm.h>

#include "lv2gtk2gui.hpp"
#include "promethee.peg"


using namespace std;
using namespace Gtk;
using namespace sigc;

class PrometheeGUI : public LV2GTK2GUI
{
public:
  PrometheeGUI(LV2Controller& ctrl,
               const std::string& URI,
               const std::string& bundle_path,
               Widget*& widget)
    : m_button("Trigger sample"), m_ctrl(ctrl)
  {

    Gtk::FileChooserDialog dialog("Choose a sample",
                                  Gtk::FILE_CHOOSER_ACTION_OPEN);
    //    dialog.set_transient_for(widget);

    //Add response buttons the the dialog:
    dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

    Gtk::FileFilter filter_samples;
    filter_samples.set_name("Audio sample Files");
    filter_samples.add_pattern("*.wav");
    filter_samples.add_pattern("*.aiff");
    dialog.add_filter(filter_samples);

    int result = dialog.run();
    dialog.hide();
    //Handle the response:
    switch(result)
      {
      case(Gtk::RESPONSE_OK):
        {
          std::cout << "Open clicked." << std::endl;
          std::string filename = dialog.get_filename();
          std::cout << "File selected: " <<  filename << std::endl;
          m_ctrl.set_file("sample", filename.c_str());
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
    widget = &m_button;

    m_button.signal_pressed().connect(bind(mem_fun(*this, &PrometheeGUI::button_clik), 0));
    m_button.signal_released().connect(bind(mem_fun(*this, &PrometheeGUI::button_clik), 1));
  }

  void                  button_clik(int a_mode)
  {
    unsigned char _on[3] = { 0x90, 1, 127 };
    unsigned char _off[3] = { 0x80, 1, 0 };

    if (a_mode == 0)
      {
        cout << "trigger on" << endl;
        m_ctrl.send_midi(peg_midi, 3, _on);
      }
    else
      {
        cout << "trigger off" << endl;
        m_ctrl.send_midi(peg_midi, 3, _off);
      }
  }
protected:
  Button                m_button;
  LV2Controller			&m_ctrl;

};

void initialise() __attribute__((constructor));
void initialise() {
  register_lv2gtk2gui<PrometheeGUI>(peg_uri);
}
