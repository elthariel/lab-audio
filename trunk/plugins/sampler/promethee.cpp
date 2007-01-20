//
// promethee.cpp for promethee in /home/elthariel/code/lab-audio/plugins/sampler
//
// Made by Elthariel
// Login   <elthariel@lse.epita.fr>
//
// Started on  Thu Jan 18 16:46:24 2007 Elthariel
// Last update Fri Jan 19 17:40:22 2007 Nahlwe
//

#include <cmath>
#include <iostream>

#include "lv2-midifunctions.h"
#include "promethee.hh"

using namespace std;


Promethee::Promethee(uint32_t rate, const char*, const LV2_Host_Feature**)
  : LV2Instrument(peg_n_ports),
    m_sample_rate(rate),
    m_sample(0)
{

}

void Promethee::run(uint32_t sample_count) {
  LV2_MIDIState       midi = {p<LV2_MIDI>(peg_midi_0), sample_count, 0};
  double              event_time;
  uint32_t            event_size;
  unsigned char       *ev;
  uint32_t            when = 0;

  /*
    if (m_sample)
    {
    when = uint32_t(lv2midi_get_event(&midi, &event_time, &event_size, &ev));
    while (event_size)
    {
    cout << "midi event received " << ev[0] << endl;
    switch(ev[0])
    {
    case 0x90:
    m_sample->note_on(50, 127);
    cout << "note_on " << endl;
    break;
    case 0x80:
    m_sample->note_off(50, 127);
    cout << "note_off " << endl;
    break;
    }
    lv2midi_step(&midi);
    when = uint32_t(lv2midi_get_event(&midi, &event_time,
    &event_size, &ev));
    }*/
  //  m_sample->render(sample_count, p<float>(peg_output_l), p<float>(peg_output_r));
        //}
}

char* Promethee::configure(const char* key, const char* value)
{
}

char* Promethee::set_file(const char* key, const char* filename)
{
  string                file = filename;
  Sample                *smp;

	smp = new Sample(filename, m_sample_rate);
  m_sample = smp;
}

void Promethee::load_file(const std::string& path)
{
}

void initialise() __attribute__((constructor));
void initialise()
{
  register_lv2_inst<Promethee>(peg_uri);
}
