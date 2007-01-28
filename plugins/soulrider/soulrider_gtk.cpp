#include <iostream>

#include <gtkmm.h>

#include "lv2gtk2gui.hpp"
#include "soulrider.peg"


using namespace std;
using namespace Gtk;
using namespace sigc;
/*
Param::Ref create_param(int port) {
	return Param::create_param(peg_ports[port].min,
														 peg_ports[port].max,
														 peg_ports[port].default_value);
}*/

class MyPluginGUI : public LV2GTK2GUI {
public:

  MyPluginGUI(LV2Controller& ctrl,
              const std::string& URI,
              const std::string& bundle_path,
              Widget*& widget)
    : m_ctrl(ctrl),
      m_btn_load_track("load"),
      m_btn_pause("pause"),
      m_btn_play("play"),
      m_btn_cue("cue"),
      m_btn_stop("stop"),
      m_btn_slowdown("slowdown"),
      m_btn_slowup("slowup"),
      m_btn_beatsmash("beatsmash"),
      m_trackname("track: "),
      m_table(4, 6, true),
      m_scale(peg_ports[peg_pitch].min, peg_ports[peg_pitch].max, 0.05),
      m_scale_pos(peg_ports[peg_position].min, peg_ports[peg_position].max, 0.01),
      m_scale_beatsmash(peg_ports[peg_beatsmasher_length].min, peg_ports[peg_beatsmasher_length].max, 0.01) {
    widget = &m_vbox;
    m_vbox.pack_start(m_table);
    m_table.attach(m_btn_load_track, 0, 2, 0, 1);
    m_table.attach(m_btn_pause, 0, 1, 1, 2);
    m_table.attach(m_btn_play, 1, 2, 1, 2);
    m_table.attach(m_btn_cue, 1, 2, 2, 3);
    m_table.attach(m_btn_stop, 0, 1, 2, 3);
    m_table.attach(m_btn_slowdown, 0, 1, 3, 4);
    m_table.attach(m_btn_slowup, 1, 2, 3, 4);
    m_table.attach(m_btn_beatsmash, 2, 3, 2, 3);
    m_table.attach(m_scale, 2, 6, 0, 1);
    m_table.attach(m_scale_pos, 2, 6, 1, 2);
    m_table.attach(m_scale_beatsmash, 3, 6, 2, 3);
    m_vbox.pack_start(m_trackname);

    m_targetlist.push_back(Gtk::TargetEntry("text/uri-list"));

    m_btn_load_track.drag_dest_set(m_targetlist);
		m_btn_load_track.drag_dest_add_uri_targets();
		m_btn_load_track.signal_drag_data_received().connect(sigc::mem_fun(*this, &MyPluginGUI::on_drop_drag_data_received));
		m_btn_load_track.signal_clicked().connect(sigc::mem_fun(*this, &MyPluginGUI::button_load_clicked));

		dropable_btn(m_btn_cue, 63);
		dropable_btn(m_btn_play, 42);
		dropable_btn(m_btn_pause, 62);
		dropable_btn(m_btn_stop, 43);
		dropable_btn(m_btn_slowdown, 65);
		dropable_btn(m_btn_slowup, 66);
		dropable_btn(m_btn_beatsmash, 67);
 		bind_param(m_scale, peg_pitch);
 		bind_param(m_scale_pos, peg_position);
 		bind_param(m_scale_beatsmash, peg_beatsmasher_length);
 		m_scale_pos.signal_value_changed().connect(sigc::bind(sigc::mem_fun(*this, &MyPluginGUI::button_clicked), 64));
 		m_scale_pos.set_update_policy(Gtk::UPDATE_DELAYED);//Gtk::UPDATE_DISCONTINUOUS
  }

	void dropable_btn(Gtk::Button &btn, int port) {
    btn.drag_dest_set(m_targetlist);
		btn.drag_dest_add_uri_targets();
		btn.signal_drag_data_received().connect(sigc::mem_fun(*this, &MyPluginGUI::on_drop_drag_data_received));
		btn.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &MyPluginGUI::button_clicked), port));
	}

	void bind_param(Gtk::Scale &param, int port) {
  	param.signal_value_changed().
    connect(compose(bind<0>(mem_fun(m_ctrl, &LV2Controller::set_control), port),
                            mem_fun(param, &Scale::get_value)));
  }
  //when a trigger button is clicked
  void button_load_clicked() {
		Gtk::FileChooserDialog dialog("Choose a file to load", Gtk::FILE_CHOOSER_ACTION_OPEN);
		Gtk::FileFilter filter_samples;

		dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
		dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

		filter_samples.set_name("Audio sample Files");
		filter_samples.add_pattern("*.wav");
		filter_samples.add_pattern("*.aiff");
		filter_samples.add_pattern("*.ogg");
		filter_samples.add_pattern("*.mp3");
		filter_samples.add_pattern("*.mpc");
		filter_samples.add_pattern("*.avi");//lol
		filter_samples.add_pattern("*.mpg");
		filter_samples.add_pattern("*.mpeg");
		dialog.add_filter(filter_samples);

		int result = dialog.run();
		if (result == Gtk::RESPONSE_OK) {
				Glib::ustring filename = dialog.get_filename();
				m_ctrl.set_file("soundfile", filename);
		}
 	}

  //when a trigger button is clicked
  void button_clicked(int note) {
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
				  	std::string filename = Glib::filename_from_uri(*it);
						m_ctrl.set_file("soundfile", filename);
						} catch (const std::exception& ex) {
						g_warning("Error while getting file info for path %s: %s", it->c_str(), ex.what());
					}
				}
			}
		}
  }

  void set_control(uint32_t port, float value) {
    if (port == peg_current_position)
      m_scale_pos.set_value(value);
  }

  /** Function for loading data from external files. */
  void set_file(const char* key, const char* filename) {
  	Glib::ustring fname(filename);
  	fname.insert(0, "track: ");
  	m_trackname.set_label(fname);
  }

protected:
  std::list<Gtk::TargetEntry> m_targetlist;
  LV2Controller &m_ctrl;
  Table m_table;
  VBox m_vbox;
  Button m_btn_load_track;
  Button m_btn_pause;
  Button m_btn_play;
  Button m_btn_cue;
  Button m_btn_stop;
  Button m_btn_slowdown;
  Button m_btn_slowup;
  Button m_btn_beatsmash;
  HScale m_scale_beatsmash;
  HScale m_scale;
  HScale m_scale_pos;
  Label m_trackname;
};


void initialise() __attribute__((constructor));
void initialise() {
  register_lv2gtk2gui<MyPluginGUI>(peg_uri);
}
