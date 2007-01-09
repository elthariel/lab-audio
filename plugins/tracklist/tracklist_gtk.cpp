#include <iostream>

#include <gtkmm.h>

#include "lv2gtk2gui.hpp"
#include "tracklist.peg"


using namespace std;
using namespace Gtk;
using namespace sigc;


class MyPluginGUI : public LV2GTK2GUI {
public:

  MyPluginGUI(LV2Controller& ctrl, const std::string& URI,
              const std::string& bundle_path, Widget*& widget)
    : m_scale(peg_ports[peg_gain].min, peg_ports[peg_gain].max, 0.01) {
    widget = &m_scale;
    m_scale.signal_value_changed().
      connect(compose(bind<0>(mem_fun(ctrl, &LV2Controller::set_control), peg_gain),
                      mem_fun(m_scale, &HScale::get_value)));
    m_scale.set_size_request(200, 50);
  }

  void set_control(uint32_t port, float value) {
    if (port == peg_gain)
      m_scale.set_value(value);
  }

protected:

  HScale m_scale;

};


void initialise() __attribute__((constructor));
void initialise() {
  register_lv2gtk2gui<MyPluginGUI>(peg_uri);
}
