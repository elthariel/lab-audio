#include <iostream>

#include <gtkmm.h>

#include "lv2gtk2gui.hpp"
#include "tronsonator.peg"
#include <thc/thc.h>
#include <thc/skinmanager.h>

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

		Thc::SkinManager::instanciate();
		Thc::SkinManager::instance()->load_all_skins();
		m_slider1 = new Thc::Slider(Thc::SkinManager::get_skin("slider/crossfader-full"));
		m_slider2 = new Thc::Slider(Thc::SkinManager::get_skin("slider/crossfader-full"));
		m_slider3 = new Thc::Slider(Thc::SkinManager::get_skin("slider/crossfader-full"));
		m_slider4 = new Thc::Slider(Thc::SkinManager::get_skin("slider/crossfader-full"));
		m_crossfader = new Thc::Slider(Thc::SkinManager::get_skin("slider/crossfader-handle-h"));
    VBox *vbox;
    widget = &m_vbox;
    m_vbox.pack_start(m_hbox);
    vbox = new VBox();
    m_hbox.pack_start(*vbox);
    vbox->pack_start(m_btn_headphone_1);
    vbox->pack_start(*m_slider1);
    vbox->pack_start(m_hbox1);
    m_hbox1.pack_start(m_cross_l1);
    m_hbox1.pack_start(m_cross_r1);

    vbox = new VBox();
    m_hbox.pack_start(*vbox);
    vbox->pack_start(m_btn_headphone_2);
    vbox->pack_start(*m_slider2);
    vbox->pack_start(m_hbox2);
    m_hbox2.pack_start(m_cross_l2);
    m_hbox2.pack_start(m_cross_r2);

    vbox = new VBox();
    m_hbox.pack_start(*vbox);
    vbox->pack_start(m_btn_headphone_3);
    vbox->pack_start(*m_slider3);
    vbox->pack_start(m_hbox3);
    m_hbox3.pack_start(m_cross_l3);
    m_hbox3.pack_start(m_cross_r3);

    vbox = new VBox();
    m_hbox.pack_start(*vbox);
    vbox->pack_start(m_btn_headphone_4);
    vbox->pack_start(*m_slider4);
    vbox->pack_start(m_hbox4);
    m_hbox4.pack_start(m_cross_l4);
    m_hbox4.pack_start(m_cross_r4);

    m_vbox.pack_start(*m_crossfader);
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
  ~MyPluginGUI() {
  	delete m_slider1;
  	delete m_slider2;
  	delete m_slider3;
  	delete m_slider4;
  	delete m_crossfader;
  }

protected:
  LV2Controller &m_ctrl;
  HBox m_hbox;
  HBox m_hbox1;
  HBox m_hbox2;
  HBox m_hbox3;
  HBox m_hbox4;
  VBox m_vbox;
  Thc::Slider *m_slider1;
  Thc::Slider *m_slider2;
  Thc::Slider *m_slider3;
  Thc::Slider *m_slider4;
  Thc::Slider *m_gain1;
  Thc::Slider *m_gain2;
  Thc::Slider *m_gain3;
  Thc::Slider *m_gain4;
  Thc::Slider *m_bal1;
  Thc::Slider *m_bal2;
  Thc::Slider *m_bal3;
  Thc::Slider *m_bal4;
  Thc::Slider *m_crossfader;
  ToggleButton m_cross_l1;
  ToggleButton m_cross_r1;
  ToggleButton m_cross_l2;
  ToggleButton m_cross_r2;
  ToggleButton m_cross_l3;
  ToggleButton m_cross_r3;
  ToggleButton m_cross_l4;
  ToggleButton m_cross_r4;
  ToggleButton m_btn_headphone_1;
  ToggleButton m_btn_headphone_2;
  ToggleButton m_btn_headphone_3;
  ToggleButton m_btn_headphone_4;
};


void initialise() __attribute__((constructor));
void initialise() {
  register_lv2gtk2gui<MyPluginGUI>(peg_uri);
}
