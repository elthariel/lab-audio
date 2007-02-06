//
// promethee.cpp for promethee in /home/elthariel/code/lab-audio/plugins/sampler
//
// Made by Elthariel
// Login   <elthariel@lse.epita.fr>
//
// Started on  Thu Jan 18 16:46:24 2007 Elthariel
// Last update Tue Feb  6 12:25:40 2007 Nahlwe
//

#include <cmath>
#include <iostream>

#include "lv2-midifunctions.h"
#include "promethee.hh"

using namespace std;


Promethee::Promethee(uint32_t rate, const char*, const LV2_Host_Feature**)
  : LV2Instrument(peg_n_ports),
    m_sample_rate(rate)
{
  int i;

  for (i = 0; i < SAMPLES_COUNT; i++)
    m_smp[i] = 0;
  TempBuffer::get(true);
}

void                    Promethee::run(uint32_t sample_count) {
  unsigned int          i;

  for (i = 0; i < SAMPLES_COUNT; i++)
    if (m_smp[i])
      {
        dispatch_control_ports(i);
        dispatch_midi_ports(i, sample_count);
        process_audio(i, sample_count);
      }
}

char*                   Promethee::configure(const char* key,
                                             const char* value)
{
  return (0);
}

char*                   Promethee::set_file(const char* key,
                                            const char* filename)
{
  unsigned int          sample_id = key[0] - '0';
  string                file(filename);

  if (sample_id < SAMPLES_COUNT)
    {
      cout << "Loading sample : " << file << endl;
      if (m_smp[sample_id])
        delete m_smp[sample_id];
      m_smp[sample_id] = new Sample(file, m_sample_rate);

    }
  return (0);
}

void                    Promethee::load_file(const std::string& path)
{
}

void                    Promethee::dispatch_control_ports(unsigned int sample_id)
{
  unsigned int          i;
  double                coefs[6];
  unsigned int          pcount = peg_fres_env_sel_0 - peg_gain_0 + 1;

  m_smp[sample_id]->set_root_note((unsigned int)(*p(peg_root_0 + pcount * sample_id)));
  m_smp[sample_id]->set_fine_pitch(*p(peg_pitch_0 + pcount * sample_id));
  m_smp[sample_id]->set_gain(*p(peg_gain_0 + pcount * sample_id));
  m_smp[sample_id]->set_pan(*p(peg_pan_0 + pcount * sample_id));
  m_smp[sample_id]->set_fcut(*p(peg_filter_cutoff_0 + pcount * sample_id));
  m_smp[sample_id]->set_fres(*p(peg_filter_res_0 + pcount * sample_id));

  for (i = 0; i < 6; i++)
    coefs[i] = *p(peg_amp_env_coef0_0 + pcount * sample_id + i);
  m_smp[sample_id]->env(EnvAmp).set_coefs((double *)&coefs, 6);

  m_smp[sample_id]->env_amount(EnvPan) = *p(peg_pan_env_amnt_0 + pcount * sample_id);
  for (i = 0; i < 6; i++)
    coefs[i] = *p(peg_pan_env_coef0_0 + pcount * sample_id + i);
  m_smp[sample_id]->env(EnvPan).set_coefs((double *)&coefs, 6);

  m_smp[sample_id]->env_amount(EnvPitch) = *p(peg_pitch_env_amnt_0 + pcount * sample_id);
  for (i = 0; i < 6; i++)
    coefs[i] = *p(peg_pitch_env_coef0_0 + pcount * sample_id + i);
  m_smp[sample_id]->env(EnvPitch).set_coefs((double *)&coefs, 6);
  // FIXME filter envs etc

  // Envelop controls
  dispatch_env_change(sample_id, EnvAmp,
                      peg_amp_env_sel_0 + pcount * sample_id);
  dispatch_env_change(sample_id, EnvPitch,
                      peg_pitch_env_sel_0 + pcount * sample_id);
  dispatch_env_change(sample_id, EnvPan,
                      peg_pan_env_sel_0 + pcount * sample_id);

  // non-rt dispatch
  m_smp[sample_id]->set_reverse(*p(peg_reverse_0 + pcount * sample_id));
  m_smp[sample_id]->set_normalize(*p(peg_normalize_0 + pcount * sample_id));
  m_smp[sample_id]->set_aalias(*p(peg_antialias_0 + pcount * sample_id));
}

void                    Promethee::dispatch_env_change(unsigned int sample_id,
                                                       EnvSelect env,
                                                       unsigned int port)
{
  EnvSwitch             &esw = m_smp[sample_id]->env(env);
  int                   val;

  val = (int) *p(port);
  esw.set_envelop(val);
}

void                    Promethee::dispatch_midi_ports(unsigned int sample_id,
                                                       unsigned int sample_count)
{
  LV2_MIDIState         midi = {p<LV2_MIDI>(peg_midi_0 + sample_id), sample_count, 0};
  double                event_time;
  uint32_t              event_size;
  unsigned char         *ev;
  uint32_t              when = 0;

  when = uint32_t(lv2midi_get_event(&midi, &event_time, &event_size, &ev));
  while (event_size)
    {
      cout << "midi event received " << ev[0] << endl;
      switch(ev[0])
        {
        case 0x90:
          m_smp[sample_id]->note_on(ev[1], ev[2]);
          cout << "note_on " << endl;
          break;
        case 0x80:
          m_smp[sample_id]->note_off(ev[1], ev[2]);
          cout << "note_off " << endl;
          break;
        }
      lv2midi_step(&midi);
      when = uint32_t(lv2midi_get_event(&midi, &event_time,
                                        &event_size, &ev));
    }
}


void                    Promethee::process_audio(unsigned int sample_id,
                                                 unsigned int sample_count)
{
  m_smp[sample_id]->render(sample_count,
           p<float>(peg_sample_0_outl + sample_id * 2),
           p<float>(peg_sample_0_outr + sample_id * 2));
}










/*
 * LV2Plugin stuffs
 */

void initialise() __attribute__((constructor));
void initialise()
{
  register_lv2_inst<Promethee>(peg_uri);
}
