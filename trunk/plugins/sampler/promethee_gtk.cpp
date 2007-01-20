//
// promethee_gtk.cpp for promethee in /home/elthariel/code/lab-audio/plugins/sampler
//
// Made by Elthariel
// Login   <elthariel@lse.epita.fr>
//
// Started on  Thu Jan 18 16:58:36 2007 Elthariel
// Last update Sat Jan 20 04:51:53 2007 Nahlwe
//

#include <iostream>
#include "promethee_gtk.hh"

using namespace std;
using namespace Gtk;
using namespace sigc;

/*
 * SampleEdit class.
 */

SampleEdit::SampleEdit(LV2Controller& ctrl, unsigned int sample_id)
  // m_main_adj(0.5, 0.0, 1.0, 0.05)
    //    m_main_scale(m_main_adj[0])
  : m_ctrl(ctrl),
    m_sample_id(sample_id),
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

  m_lbl_main[0].set_label("_Vol_");
  m_lbl_main[1].set_label("_Pan_");
  m_lbl_main[2].set_label("_Pitch_");
  m_lbl_main[3].set_label("_Root_");
  m_vbox_main[0].pack_start(m_main_scale_vol);
  m_vbox_main[1].pack_start(m_main_scale_pan);
  m_vbox_main[2].pack_start(m_main_scale_pitch);
  m_vbox_main[3].pack_start(m_main_scale_root);
  for (i = 0; i < 4; i++)
    {
      m_vbox_main[i].pack_start(m_lbl_main[i]);
      m_vbox[sedit_main].pack_start(m_vbox_main[i]);
    }

  m_main_scale_vol.signal_change_value().connect(mem_fun(*this, &SampleEdit::set_vol));
  m_main_scale_pan.signal_change_value().connect(mem_fun(*this, &SampleEdit::set_pan));
  m_main_scale_pitch.signal_change_value().connect(mem_fun(*this, &SampleEdit::set_pitch));
  m_main_scale_root.signal_change_value().connect(mem_fun(*this, &SampleEdit::set_root));
}

void                    SampleEdit::set_sample_id(unsigned int sid)
{
  m_sample_id = sid;
}

void                    SampleEdit::set_vol(Gtk::ScrollType st, double val)
{
  m_ctrl.set_control(peg_gain_0, val);
}

void                    SampleEdit::set_pan(Gtk::ScrollType st, double val)
{
  m_ctrl.set_control(peg_pan_0, val);
}

void                    SampleEdit::set_pitch(Gtk::ScrollType st, double val)
{
  m_ctrl.set_control(peg_pitch_0, val);
}

void                    SampleEdit::set_root(Gtk::ScrollType st, double val)
{
  m_ctrl.set_control(peg_root_0, val);
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
      m_smp_edit.push_back(new SampleEdit(m_ctrl, i));
      m_smp_notebook.append_page(*m_smp_edit[i], "_fRe3_");
    }
  /*  m_button.signal_released().connect(bind(mem_fun(*this,
                                                  &PrometheeGUI::button_clik), 1));
  */
}

void initialise() __attribute__((constructor));
void initialise() {
  register_lv2gtk2gui<PrometheeGUI>(peg_uri);
}
