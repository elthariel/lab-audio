//
// promethee_gtk.cpp for promethee in /home/elthariel/code/lab-audio/plugins/sampler
//
// Made by Elthariel
// Login   <elthariel@lse.epita.fr>
//
// Started on  Thu Jan 18 16:58:36 2007 Elthariel
// Last update Mon Feb  5 05:36:10 2007 Nahlwe
//

#include <iostream>
#include "promethee_gtk.hh"

using namespace std;
using namespace Gtk;
using namespace sigc;

/*
 * EnvEdit class
 */

void                  EnvEdit::bind_scale(Adjustment &sc,
                                          unsigned int port)
{
  sc.signal_value_changed().
    connect(compose(bind<0>(mem_fun(m_ctrl, &LV2Controller::set_control), port),
                    mem_fun(sc, &Adjustment::get_value)));
}

void                  EnvEdit::bind_radio(RadioButton &bu,
                                          int but_num,
                                          unsigned int port)
{
  bu.signal_toggled().
    connect(compose(bind<0>(bind<0>(mem_fun(*this, &EnvEdit::radio_check),
                                    port),
                            but_num),
                    mem_fun(bu, &RadioButton::get_active)));
}

void                  EnvEdit::radio_check(unsigned int port,
                                           int button,
                                           bool val)
{
  if (val)
    {
      m_ctrl.set_control(port, (double) button);
    }
}

EnvEdit::EnvEdit(LV2Controller& ctrl, unsigned int sample_id,
                 unsigned int base_peg, bool amount)
  : m_ctrl(ctrl),
    m_amount(0.0, -1.0, 1.0, 0.01),
    m_coef0(1.0, 0.0, 16.0, 0.01),
    m_coef1(1.0, 0.0, 16.0, 0.01),
    m_coef2(1.0, 0.0, 16.0, 0.01),
    m_coef3(1.0, 0.0, 16.0, 0.01),
    m_coef4(1.0, 0.0, 16.0, 0.01),
    m_coef5(1.0, 0.0, 16.0, 0.01),
    m_scale_amount(m_amount),
    m_scale0(m_coef0),
    m_scale1(m_coef1),
    m_scale2(m_coef2),
    m_scale3(m_coef3),
    m_scale4(m_coef4),
    m_scale5(m_coef5),
    m_env_none("Disable"),
    m_env_decay("Decay"),
    m_env_hold("Hold"),
    m_env_dahdsr("Dahdsr")
{
  m_env_none.set_group(m_env_select);
  m_env_decay.set_group(m_env_select);
  m_env_hold.set_group(m_env_select);
  m_env_dahdsr.set_group(m_env_select);
  m_env_none.set_active();
  m_env_hbox.pack_start(m_env_none);
  m_env_hbox.pack_start(m_env_decay);
  m_env_hbox.pack_start(m_env_hold);
  m_env_hbox.pack_start(m_env_dahdsr);

  pack_start(m_env_hbox);
  pack_start(m_hbox);
  m_hbox.pack_start(m_scale0);
  m_hbox.pack_start(m_scale1);
  m_hbox.pack_start(m_scale2);
  m_hbox.pack_start(m_scale3);
  m_hbox.pack_start(m_scale4);
  m_hbox.pack_start(m_scale5);
  if (amount)
    m_hbox.pack_start(m_scale_amount);

  // Connect all this
  if (amount)
    {
      bind_scale(m_amount, base_peg);
      ++base_peg;
    }
  bind_scale(m_coef0, base_peg++);
  bind_scale(m_coef1, base_peg++);
  bind_scale(m_coef2, base_peg++);
  bind_scale(m_coef3, base_peg++);
  bind_scale(m_coef4, base_peg++);
  bind_scale(m_coef5, base_peg++);

  bind_radio(m_env_none, -1,  base_peg);
  bind_radio(m_env_decay, 0,  base_peg);
  bind_radio(m_env_hold, 1,  base_peg);
  bind_radio(m_env_dahdsr, 2,  base_peg);
}

/*
 * SampleEdit class.
 */

SampleEdit::SampleEdit(LV2Controller& ctrl, unsigned int sample_id)
  // m_main_adj(0.5, 0.0, 1.0, 0.05)
    //    m_main_scale(m_main_adj[0])
  : m_ctrl(ctrl),
    m_sample_id(sample_id),
    m_pcount(peg_fres_env_sel_0 - peg_gain_0 + 1),
    m_rev("Reverse"),
    m_norm("Normalize"),
    m_aalias("AntiAlias"),
    m_amp_env(ctrl, sample_id, peg_amp_env_coef0_0 + sample_id * m_pcount, false),
    m_pan_env(ctrl, sample_id, peg_pan_env_amnt_0 + sample_id * m_pcount),
    m_pitch_env(ctrl, sample_id, peg_pitch_env_amnt_0 + sample_id * m_pcount),
    m_fcut_env(ctrl, sample_id, peg_fcut_env_amnt_0 + sample_id * m_pcount),
    m_fres_env(ctrl, sample_id, peg_fres_env_amnt_0 + sample_id * m_pcount),
    m_main_adj_vol(1.0, 0.0, 2.0, 0.01),
    m_main_adj_pan(0.5, 0.0, 1.0, 0.01),
    m_main_adj_pitch(1.0, 0.0, 2.0, 0.01),
    m_main_adj_root(63.0, 0.0, 127.0, 1.0),
    m_main_scale_vol(m_main_adj_vol),
    m_main_scale_pan(m_main_adj_pan),
    m_main_scale_pitch(m_main_adj_pitch),
    m_main_scale_root(m_main_adj_root),
    m_sample_path(" *-= Please load a sample =-*"),
    m_choose_sample(Stock::OPEN)
{
  int i;

  for (i = 0; i < sedit_n_hbox; i++)
    this->pack_start(m_hbox[i]);

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
      m_hbox[sedit_main].pack_start(m_vbox_main[i]);
    }
  m_hbox[sedit_load].pack_start(m_choose_sample);
  m_hbox[sedit_load].pack_start(m_sample_path);

  m_main_scale_vol.signal_change_value().connect(mem_fun(*this, &SampleEdit::set_vol));
  m_main_scale_pan.signal_change_value().connect(mem_fun(*this, &SampleEdit::set_pan));
  m_main_scale_pitch.signal_change_value().connect(mem_fun(*this, &SampleEdit::set_pitch));
  m_main_scale_root.signal_change_value().connect(mem_fun(*this, &SampleEdit::set_root));
  m_choose_sample.signal_clicked().connect(mem_fun(*this, &SampleEdit::choose_sample));

  // Init envelops edit & co
  m_hbox[sedit_env].pack_start(m_env_notebook);
  m_env_notebook.append_page(m_amp_env, "Amp");
  m_env_notebook.append_page(m_pan_env, "Pan");
  m_env_notebook.append_page(m_pitch_env, "Pitch");
  m_env_notebook.append_page(m_fcut_env, "Filter cutoff");
  m_env_notebook.append_page(m_fres_env, "Filter resonance");

  // (Waveview &) non-rt features.
  m_hbox[sedit_smp].pack_end(m_nonrt_vbox);
  m_nonrt_vbox.pack_start(m_rev);
  m_nonrt_vbox.pack_start(m_norm);
  m_nonrt_vbox.pack_start(m_aalias);
  m_rev.signal_toggled().
    connect(compose(bind<0>(mem_fun(m_ctrl, &LV2Controller::set_control),
                            peg_reverse_0 + sample_id * m_pcount),
                    mem_fun(m_rev, &CheckButton::get_active)));
  m_rev.signal_toggled().
    connect(compose(bind<0>(mem_fun(m_ctrl, &LV2Controller::set_control),
                            peg_normalize_0 + sample_id * m_pcount),
                    mem_fun(m_norm, &CheckButton::get_active)));
  m_rev.signal_toggled().
    connect(compose(bind<0>(mem_fun(m_ctrl, &LV2Controller::set_control),
                            peg_antialias_0 + sample_id * m_pcount),
                    mem_fun(m_aalias, &CheckButton::get_active)));

}

void                    SampleEdit::set_sample_id(unsigned int sid)
{
  m_sample_id = sid;
}

bool                    SampleEdit::set_vol(Gtk::ScrollType st, double val)
{
  m_ctrl.set_control(peg_gain_0 + m_sample_id * m_pcount, val);
  return (true);
}

bool                    SampleEdit::set_pan(Gtk::ScrollType st, double val)
{
  m_ctrl.set_control(peg_pan_0 + m_sample_id * m_pcount, val);
  return (true);
}

bool                    SampleEdit::set_pitch(Gtk::ScrollType st, double val)
{
  m_ctrl.set_control(peg_pitch_0 + m_sample_id * m_pcount, val);
  return (true);
}

bool                    SampleEdit::set_root(Gtk::ScrollType st, double val)
{
  m_ctrl.set_control(peg_root_0 + m_sample_id * m_pcount, val);
  return (true);
}

void SampleEdit::on_drop_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context,
                                            int,
                                            int,
                                            const Gtk::SelectionData& selection_data,
                                            guint,
                                            guint time)
{
  /*  if (selection_data.get_data())
    {
      std::vector<Glib::ustring> targets = selection_data.get_uris();
      if (! targets.empty())
        {
          for (std::vector<Glib::ustring>::iterator it(targets.begin()); it != targets.end(); ++it) {
            try
              {
                m_ctrl.set_file((char *)m_sample_id, it->c_str());
              }
            catch (const std::exception& ex)
              {
                g_warning("Error while getting file info for path %s: %s", it->c_str(), ex.what());
              }
          }
        }
        }*/
}

void                  SampleEdit::choose_sample()
{
  Gtk::FileChooserDialog dialog("Choose a sample to load",
                                Gtk::FILE_CHOOSER_ACTION_OPEN);
  //  dialog.set_transient_for(*this);

  //Add response buttons the the dialog:
  dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

  Gtk::FileFilter filter_samples;
  filter_samples.set_name("Audio sample Files");
  filter_samples.add_pattern("*.wav");
  filter_samples.add_pattern("*.aiff");
  dialog.add_filter(filter_samples);

  int result = dialog.run();
  dialog.hide();
  //Handle the response:
  switch(result)
  {
    case(Gtk::RESPONSE_OK):
    {
      char c_chan[8];
      c_chan[0] = m_sample_id + '0';
      c_chan[1] = 0;
      string channel;
      channel = c_chan;
      cout << "Open clicked." << endl;
      string filename = dialog.get_filename();
      cout << "File selected: " <<  filename << endl;
      m_ctrl.set_file(channel, filename);
      //      m_ctrl.set_file((char *)m_sample_id, filename.c_str());
      m_sample_path.set_label(filename);
      break;
    }
    case(Gtk::RESPONSE_CANCEL):
    {
      std::cout << "Cancel clicked." << std::endl;
      break;
    }
    default:
    {
      std::cout << "Unexpected button clicked." << std::endl;
      break;
    }
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
      m_smp_edit.push_back(new SampleEdit(m_ctrl, i));
      m_smp_notebook.append_page(*m_smp_edit[i], "_(free)_");
    }
}

void initialise() __attribute__((constructor));
void initialise() {
  register_lv2gtk2gui<PrometheeGUI>(peg_uri);
}
