//
// promethee.cpp for promethee in /home/elthariel/code/lab-audio/plugins/sampler
//
// Made by Elthariel
// Login   <elthariel@lse.epita.fr>
//
// Started on  Thu Jan 18 16:46:24 2007 Elthariel
// Last update Sat Jan 20 10:23:28 2007 Nahlwe
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
  unsigned int          sample_id = (unsigned int)(key);
  string                file(filename);

  cout << "Loading sample : " << file << endl;
  if (sample_id < SAMPLES_COUNT)
    if (m_smp[sample_id])
      delete m_smp[sample_id];
    else
      {
        m_smp[sample_id] = new Sample(file, m_sample_rate);
      }
  return (0);
}

void                    Promethee::load_file(const std::string& path)
{
}

void                    Promethee::dispatch_control_ports(unsigned int sample_id)
{
  m_smp[sample_id]->set_root_note((unsigned int)(*p<float>(peg_root_0 + 4 * sample_id)));
  m_smp[sample_id]->set_fine_pitch(*p<float>(peg_pitch_0 + 4 * sample_id));
  m_smp[sample_id]->set_gain(*p<float>(peg_gain_0 + 4 * sample_id));
  m_smp[sample_id]->set_pan(*p<float>(peg_pan_0 + 4 * sample_id));
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
                           p<float>(sample_id * 2),
                           p<float>(sample_id * 2 + 1));
}










/*
 * LV2Plugin stuffs
 */

void initialise() __attribute__((constructor));
void initialise()
{
  register_lv2_inst<Promethee>(peg_uri);
}
