#include <iostream>

#include <gtkmm.h>

#include "lv2gtk2gui.hpp"
#include "tronsonator.peg"
#include <thc/thc.h>
#include <thc/skinmanager.h>

using namespace std;
using namespace Gtk;
using namespace sigc;
using namespace Thc;


Param::Ref create_param(int port) {
	return Param::create_param(peg_ports[port].min,
														 peg_ports[port].max,
														 peg_ports[port].default_value);
}

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
      m_btn_headphone_4("h"),
      m_gain1(create_param(peg_gain_1)),
      m_gain2(create_param(peg_gain_2)),
      m_gain3(create_param(peg_gain_3)),
      m_gain4(create_param(peg_gain_4)),
      m_slider1(SkinManager::get_skin("slider/crossfader-handle-v"), create_param(peg_volume_1), true),
			m_slider2(SkinManager::get_skin("slider/crossfader-handle-v"), create_param(peg_volume_2), true),
			m_slider3(SkinManager::get_skin("slider/crossfader-handle-v"), create_param(peg_volume_3), true),
			m_slider4(SkinManager::get_skin("slider/crossfader-handle-v"), create_param(peg_volume_4), true),
			m_crossfader(SkinManager::get_skin("slider/crossfader-handle-h"), create_param(peg_crossfader), true) {
    VBox *vbox;
    widget = &m_vbox;
    m_vbox.pack_start(m_hbox);
    vbox = new VBox();
    m_hbox.pack_start(*vbox);
    vbox->pack_start(m_btn_headphone_1);
    vbox->pack_start(m_bal1);
    vbox->pack_start(m_gain1);
    vbox->pack_start(m_slider1);
    vbox->pack_start(m_hbox1);
    m_hbox1.pack_start(m_cross_l1);
    m_hbox1.pack_start(m_cross_r1);

    vbox = new VBox();
    m_hbox.pack_start(*vbox);
    vbox->pack_start(m_btn_headphone_2);
    vbox->pack_start(m_bal2);
    vbox->pack_start(m_gain2);
    vbox->pack_start(m_slider2);
    vbox->pack_start(m_hbox2);
    m_hbox2.pack_start(m_cross_l2);
    m_hbox2.pack_start(m_cross_r2);

    vbox = new VBox();
    m_hbox.pack_start(*vbox);
    vbox->pack_start(m_btn_headphone_3);
    vbox->pack_start(m_bal3);
    vbox->pack_start(m_gain3);
    vbox->pack_start(m_slider3);
    vbox->pack_start(m_hbox3);
    m_hbox3.pack_start(m_cross_l3);
    m_hbox3.pack_start(m_cross_r3);

    vbox = new VBox();
    m_hbox.pack_start(*vbox);
    vbox->pack_start(m_btn_headphone_4);
    vbox->pack_start(m_bal4);
    vbox->pack_start(m_gain4);
    vbox->pack_start(m_slider4);
    vbox->pack_start(m_hbox4);
    m_hbox4.pack_start(m_cross_l4);
    m_hbox4.pack_start(m_cross_r4);

    m_vbox.pack_start(m_crossfader);

		bind_param(m_gain1.get_param("x"), peg_gain_1);
		bind_param(m_gain2.get_param("x"), peg_gain_2);
		bind_param(m_gain3.get_param("x"), peg_gain_3);
		bind_param(m_gain4.get_param("x"), peg_gain_4);
    bind_param(m_slider1.get_param("x"), peg_volume_1);
    bind_param(m_slider2.get_param("x"), peg_volume_2);
    bind_param(m_slider3.get_param("x"), peg_volume_3);
    bind_param(m_slider4.get_param("x"), peg_volume_4);
    bind_param(m_crossfader.get_param("x"), peg_crossfader);
    bind_param2(m_btn_headphone_1, peg_headphone_1);
    bind_param2(m_btn_headphone_2, peg_headphone_2);
    bind_param2(m_btn_headphone_3, peg_headphone_3);
    bind_param2(m_btn_headphone_4, peg_headphone_4);
    bind_param3(m_cross_l1, m_cross_r1, 1, 2);
    bind_param3(m_cross_l2, m_cross_r2, 1, 2);
    bind_param3(m_cross_l3, m_cross_r3, 1, 2);
    bind_param3(m_cross_l4, m_cross_r4, 1, 2);

  }
  void bind_param(Thc::Param::Ref param, int port) {
  	param->signal_value_changed().
    connect(compose(bind<0>(mem_fun(m_ctrl, &LV2Controller::set_control), port),
                            mem_fun(*param, &Thc::Param::get_value)));
  }

  void bind_param2(Gtk::ToggleButton& param, int port) {
  	param.signal_toggled().
    connect(compose(bind<0>(mem_fun(m_ctrl, &LV2Controller::set_control), port),
                            mem_fun(param, &ToggleButton::get_active)));
  }

  void bind_param3(Gtk::ToggleButton& param1, Gtk::ToggleButton& param2, int port1, int port2) {
  	param1.signal_toggled().
    connect(bind(mem_fun(*this, &MyPluginGUI::cross_toggle), &param1, &param2, port1, port2));
  	param2.signal_toggled().
    connect(bind(mem_fun(*this, &MyPluginGUI::cross_toggle), &param2, &param1, port2, port1));
  }

  void cross_toggle(Gtk::ToggleButton* param1, Gtk::ToggleButton* param2, int port1, int port2) {
  	bool active = param1->get_active();
  	//m_ctrl.set_control(port1, active);
  	if (param2->get_active() == active && active) {
  		param2->set_active(!active);
  		//m_ctrl.set_control(port2, !active);
  	}
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
  HBox m_hbox1;
  HBox m_hbox2;
  HBox m_hbox3;
  HBox m_hbox4;
  VBox m_vbox;
  Thc::Slider m_slider1;
  Thc::Slider m_slider2;
  Thc::Slider m_slider3;
  Thc::Slider m_slider4;
  Thc::Slider m_gain1;
  Thc::Slider m_gain2;
  Thc::Slider m_gain3;
  Thc::Slider m_gain4;
  Thc::Slider m_bal1;
  Thc::Slider m_bal2;
  Thc::Slider m_bal3;
  Thc::Slider m_bal4;
  Thc::Slider m_crossfader;
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
