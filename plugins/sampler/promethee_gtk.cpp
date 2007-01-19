//
// promethee_gtk.cpp for promethee in /home/elthariel/code/lab-audio/plugins/sampler
//
// Made by Elthariel
// Login   <elthariel@lse.epita.fr>
//
// Started on  Thu Jan 18 16:58:36 2007 Elthariel
// Last update Fri Jan 19 08:52:09 2007 Nahlwe
//

#include <iostream>
#include "promethee_gtk.hh"

using namespace std;
using namespace Gtk;
using namespace sigc;

/*
 * SampleEdit class.
 */

SampleEdit::SampleEdit(LV2Controller& ctrl)
  // m_main_adj(0.5, 0.0, 1.0, 0.05)
    //    m_main_scale(m_main_adj[0])
  : m_ctrl(ctrl),
    m_main_adj_vol(1.0, 0.0, 2.0, 0.01),
    m_main_adj_pan(1.0, 0.0, 2.0, 0.01),
    m_main_adj_pitch(1.0, 0.0, 2.0, 0.01),
    m_main_adj_root(63.0, 0.0, 127.0, 1.0),
    m_main_scale_vol(m_main_adj_vol),
    m_main_scale_pan(m_main_adj_pan),
    m_main_scale_pitch(m_main_adj_pitch),
    m_main_scale_root(m_main_adj_root)
{
  int i;

  for (i = 0; i < sedit_n_hbox; i++)
    this->pack_start(m_vbox[i]);

  m_lbl_main[0].set_label("Vol");
  m_lbl_main[1].set_label("Pan");
  m_lbl_main[2].set_label("Pitch");
  m_lbl_main[3].set_label("Root");
  m_vbox_main[0].pack_start(m_main_scale_vol);
  m_vbox_main[1].pack_start(m_main_scale_pan);
  m_vbox_main[2].pack_start(m_main_scale_pitch);
  m_vbox_main[3].pack_start(m_main_scale_root);
  for (i = 0; i < 4; i++)
    {
      m_vbox_main[i].pack_start(m_lbl_main[i]);
      m_vbox[sedit_main].pack_start(m_vbox_main[i]);
    }
}

/*
 * PrometheeGUI class.
 */

PrometheeGUI::PrometheeGUI(LV2Controller& ctrl,
                           const std::string& URI,
                           const std::string& bundle_path,
                           Widget*& widget)
  :m_ctrl(ctrl)
{
  int i;

  widget = &m_smp_notebook;
  m_smp_notebook.set_tab_pos(POS_LEFT);

  for (i = 0; i < SAMPLES_COUNT; i++)
    {
      m_smp_notebook.append_page(m_smp_edit[i], "_fRe3_");
    }
  /*  m_button.signal_released().connect(bind(mem_fun(*this,
                                                  &PrometheeGUI::button_clik), 1));
  */
}

void initialise() __attribute__((constructor));
void initialise() {
  register_lv2gtk2gui<PrometheeGUI>(peg_uri);
}
