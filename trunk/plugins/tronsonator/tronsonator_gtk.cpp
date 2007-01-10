#include <iostream>

#include <gtkmm.h>

#include "lv2gtk2gui.hpp"
#include "tronsonator.peg"


using namespace std;
using namespace Gtk;
using namespace sigc;


class MyPluginGUI : public LV2GTK2GUI {
public:

  MyPluginGUI(LV2Controller& ctrl,
              const std::string& URI,
              const std::string& bundle_path,
              Widget*& widget)
    : m_ctrl(ctrl),
      m_btn_headphone_l("h"),
      m_btn_headphone_r("h") {
    widget = &m_hbox;
    m_hbox.pack_start(m_hbox);
    m_hbox.pack_start(m_btn_load_track);
    m_hbox.pack_start(m_btn_pause);
    m_hbox.pack_start(m_btn_play);
    m_hbox.pack_start(m_btn_cue);

    m_targetlist.push_back(Gtk::TargetEntry("text/uri-list"));
    m_btn_load_track.drag_dest_set(m_targetlist);
		m_btn_load_track.drag_dest_add_uri_targets();
		m_btn_load_track.signal_drag_data_received().connect(sigc::mem_fun(*this, &MyPluginGUI::on_drop_drag_data_received));
		m_btn_load_track.signal_clicked().connect(sigc::mem_fun(*this, &MyPluginGUI::button_load_clicked));

		m_btn_pause.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &MyPluginGUI::button_clicked), 42));
		m_btn_cue.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &MyPluginGUI::button_clicked), 43));
		m_btn_play.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &MyPluginGUI::button_clicked), 44));
  }

  //when a trigger button is clicked
  void button_headphone() {
  	std::cout << "gtk: loading" << std::endl;
  }

  //when a trigger button is clicked
  void button_clicked(int note) {
    std::cout << "Note: " << note << std::endl;
    unsigned char data_on[3] = { 0x90, note, 127 };
    unsigned char data_off[3] = { 0x80, note, 0 };
    m_ctrl.send_midi(peg_midi, 3, data_on);
    m_ctrl.send_midi(peg_midi, 3, data_off);
  }

protected:
  LV2Controller &m_ctrl;
  HBox m_hbox;
  VBox m_vbox;
  HScale m_slider1;
  HScale m_slider2;
  HScale m_slider3;
  Hscale m_slider4;
  HScale m_crossfader;
  Button m_cross_l1;
  Button m_cross_r1;
  Button m_cross_l2;
  Button m_cross_r2;
  Button m_cross_l3;
  Button m_cross_r3;
  Button m_cross_l4;
  Button m_cross_r4;

};


void initialise() __attribute__((constructor));
void initialise() {
  register_lv2gtk2gui<MyPluginGUI>(peg_uri);
}
