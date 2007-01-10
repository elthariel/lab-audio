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
      m_btn_load_track("load track"),
      m_btn_pause("pause"),
      m_btn_play("play"),
      m_btn_cue("cue") {
    widget = &m_hbox;
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
  void button_load_clicked() {
  	std::cout << "gtk: loading" << std::endl;
    m_ctrl.set_file("file", "/tamere/mp3/SPEEEEEEEEEEEEDCORE");
    m_ctrl.configure("file", "/tamere/mp3/SPEEEEEEEEEEEEDCORE");
  }

  //when a trigger button is clicked
  void button_clicked(int note) {
    std::cout << "Note: " << note << std::endl;
    unsigned char data_on[3] = { 0x90, note, 127 };
    unsigned char data_off[3] = { 0x80, note, 0 };
    m_ctrl.send_midi(peg_midi, 3, data_on);
    m_ctrl.send_midi(peg_midi, 3, data_off);
  }

  void on_drop_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context,
  															  int,
  															  int,
  															  const Gtk::SelectionData& selection_data,
  															  guint,
  															  guint time) {
    if (selection_data.get_data()) {
      std::vector<Glib::ustring> targets = selection_data.get_uris();
      if (! targets.empty()) {
      	for (std::vector<Glib::ustring>::iterator it(targets.begin()); it != targets.end(); ++it) {
				  try {
						m_ctrl.configure("file", *it);
						} catch (const std::exception& ex) {
						g_warning("Error while getting file info for path %s: %s", it->c_str(), ex.what());
					}
				}
			}
		}
  }

protected:
  std::list<Gtk::TargetEntry> m_targetlist;
  LV2Controller &m_ctrl;
  HBox m_hbox;
  Button m_btn_load_track;
  Button m_btn_pause;
  Button m_btn_play;
  Button m_btn_cue;
};


void initialise() __attribute__((constructor));
void initialise() {
  register_lv2gtk2gui<MyPluginGUI>(peg_uri);
}
