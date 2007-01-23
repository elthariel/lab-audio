
#include "10tau_gtk.hh"

using namespace sigc;

TauGUI::TauGUI(LV2Controller& controller, const char* plugin_URI,
               const char* bundle_path, Gtk::Widget*& widget)
  : m_ctrl(controller),
    m_adj1(0.0, 1.0, 0.0, 0.01), m_adj2(0.0, 1.0, 0.0, 0.01),
    m_scale1(m_adj1), m_scale2(m_adj2)
{
  widget = &m_hbox;

  m_hbox.pack_start(m_scale1);
  m_hbox.pack_start(m_scale2);
  m_scale1.signal_change_value().connect(mem_fun(*this, &TauGUI::chg_param_1));
  m_scale2.signal_change_value().connect(mem_fun(*this, &TauGUI::chg_param_2));
}

bool                    TauGUI::chg_param_1(Gtk::ScrollType,
                                            double val)
{
  m_ctrl.set_control(peg_param_1, val);
  return (true);
}

bool                    TauGUI::chg_param_2(Gtk::ScrollType,
                                            double val)
{
  m_ctrl.set_control(peg_param_2, val);
  return (true);
}

void initialise() __attribute__((constructor));
void initialise() {
  register_lv2gtk2gui<TauGUI>(peg_uri);
}
