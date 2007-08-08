
//
// promethee.cpp for promethee in /home/elthariel/code/lab-audio/plugins/sampler
//
// Made by Elthariel
// Login   <elthariel@lse.epita.fr>
//
// Started on  Thu Jan 18 16:46:24 2007 Elthariel
// Last update Sat Jul 21 17:13:50 2007 Nahlwe
//

#include <cmath>
#include <iostream>

#include "lv2-midifunctions.h"
#include "promethee.hh"

using namespace std;


Promethee::Promethee(uint32_t rate, const char*, const LV2_Host_Feature**)
  : LV2Instrument(peg_n_ports),
    m_sample_rate(rate),
    m_smp(rate)
{
}

void                    Promethee::run(uint32_t sample_count) {
  dispatch_control_ports();
  dispatch_midi_ports(sample_count);
  process_audio(sample_count);
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

  return (0);
}

void                    Promethee::load_file(const std::string& path)
{
}

void                    Promethee::dispatch_control_ports()
{
  unsigned int          i;
  double                coefs[6];

  m_smp.set_root_note((unsigned int)(*p(peg_root)));
  m_smp.set_fine_pitch(*p(peg_pitch));
  m_smp.set_gain(*p(peg_gain));
  m_smp.set_pan(*p(peg_pan));
  m_smp.set_fcut(*p(peg_filter_cutoff));
  m_smp.set_fres(*p(peg_filter_res));

  for (i = 0; i < 6; i++)
    coefs[i] = *p(peg_amp_env_coef0 + i);
  m_smp.env(EnvAmp).set_coefs((double *)&coefs, 6);

  m_smp.env_amount(EnvPan) = *p(peg_pan_env_amnt);
  for (i = 0; i < 6; i++)
    coefs[i] = *p(peg_pan_env_coef0 + i);
  m_smp.env(EnvPan).set_coefs((double *)&coefs, 6);

  m_smp.env_amount(EnvPitch) = *p(peg_pitch_env_amnt);
  for (i = 0; i < 6; i++)
    coefs[i] = *p(peg_pitch_env_coef0 + i);
  m_smp.env(EnvPitch).set_coefs((double *)&coefs, 6);
  // FIXME filter envs etc

  // Envelop controls
  dispatch_env_change(EnvAmp, peg_amp_env_sel);
  dispatch_env_change(EnvPitch, peg_pitch_env_sel);
  dispatch_env_change(EnvPan, peg_pan_env_sel);

  // non-rt dispatch
  m_smp.set_reverse(*p(peg_reverse));
  m_smp.set_normalize(*p(peg_normalize));
  m_smp.set_aalias(*p(peg_antialias));
}

void                    Promethee::dispatch_env_change(EnvSelect env,
                                                       unsigned int port)
{
  EnvSwitch             &esw = m_smp.env(env);
  int                   val;

  val = (int) *p(port);
  esw.set_envelop(val);
}

void                    Promethee::dispatch_midi_ports(unsigned int sample_count)
{
  LV2_MIDIState         midi = {p<LV2_MIDI>(peg_midi), sample_count, 0};
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
          m_smp.note_on(ev[1], ev[2]);
          cout << "note_on " << endl;
          break;
        case 0x80:
          m_smp.note_off(ev[1], ev[2]);
          cout << "note_off " << endl;
          break;
        }
      lv2midi_step(&midi);
      when = uint32_t(lv2midi_get_event(&midi, &event_time,
                                        &event_size, &ev));
    }
}


void                    Promethee::process_audio(unsigned int sample_count)
{
  m_smp.render(sample_count,
               p<float>(peg_sample_outl),
               p<float>(peg_sample_outr));
}










/*
 * LV2Plugin stuffs
 */

void initialise() __attribute__((constructor));
void initialise()
{
  register_lv2_inst<Promethee>(peg_uri);
}
