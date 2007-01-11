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
      m_cross_l1("<"),
  		m_cross_r1(">"),
  		m_cross_l2("<"),
  		m_cross_r2(">"),
  		m_cross_l3("<"),
  		m_cross_r3(">"),
  		m_cross_l4("<"),
  		m_cross_r4(">"),
      m_btn_headphone_1("h"),
      m_btn_headphone_2("h"),
      m_btn_headphone_3("h"),
      m_btn_headphone_4("h") {
    VBox *vbox;
    widget = &m_vbox;
    m_vbox.pack_start(m_hbox);
    vbox = new VBox();
    m_hbox.pack_start(*vbox);
    vbox->pack_start(m_btn_headphone_1);
    vbox->pack_start(m_slider1);
    vbox->pack_start(m_cross_l1);
    vbox->pack_start(m_cross_r1);

    vbox = new VBox();
    m_hbox.pack_start(*vbox);
    vbox->pack_start(m_btn_headphone_2);
    vbox->pack_start(m_slider2);
    vbox->pack_start(m_cross_l2);
    vbox->pack_start(m_cross_r2);

    vbox = new VBox();
    m_hbox.pack_start(*vbox);
    vbox->pack_start(m_btn_headphone_3);
    vbox->pack_start(m_slider3);
    vbox->pack_start(m_cross_l3);
    vbox->pack_start(m_cross_r3);

    vbox = new VBox();
    m_hbox.pack_start(*vbox);
    vbox->pack_start(m_btn_headphone_4);
    vbox->pack_start(m_slider4);
    vbox->pack_start(m_cross_l4);
    vbox->pack_start(m_cross_r4);

    m_vbox.pack_start(m_crossfader);
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
  HScale m_slider4;
  HScale m_crossfader;
  Button m_cross_l1;
  Button m_cross_r1;
  Button m_cross_l2;
  Button m_cross_r2;
  Button m_cross_l3;
  Button m_cross_r3;
  Button m_cross_l4;
  Button m_cross_r4;
  Button m_btn_headphone_1;
  Button m_btn_headphone_2;
  Button m_btn_headphone_3;
  Button m_btn_headphone_4;
};


void initialise() __attribute__((constructor));
void initialise() {
  register_lv2gtk2gui<MyPluginGUI>(peg_uri);
}
