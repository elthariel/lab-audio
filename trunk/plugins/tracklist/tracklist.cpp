/****************************************************************************

    myplugin.cpp - example file for writing LV2 plugins in C++

    Copyright (C) 2006  Lars Luthman <lars.luthman@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 01222-1307  USA

****************************************************************************/

#include <cmath>

#include "lv2plugin.hpp"
#include "lv2-miditype.h"
#include "lv2-midifunctions.h"
#include "tracklist.peg"


/** This is the class that contains all the code and data for the plugin. */
class MyPlugin : public LV2Plugin {
public:

  /** The first parameter is the sample rate, the second is the path to the
      LV2 bundle, the third is the host features supported by this host. */
  MyPlugin(uint32_t rate, const char*, const LV2_Host_Feature**)
    : LV2Plugin(peg_n_ports),
      m_phase(0),
      m_increment(0),
      m_invrate(1.0 / rate) {

  }

  /** The run() callback. This is the function that gets called by the host
      when it wants to run the plugin. The parameter is the number of sample
      frames to process. */
  void run(uint32_t sample_count) {

    LV2_MIDIState midi = { p<LV2_MIDI>(peg_midi), sample_count, 0 };

    double event_time;
    uint32_t event_size;
    unsigned char* event;
    uint32_t now = 0;
    uint32_t then;

    while (now < sample_count) {
      then = uint32_t(lv2midi_get_event(&midi, &event_time,
                                        &event_size, &event));
      for (uint32_t i = now; i < then; ++i) {
        p<float>(peg_output)[i] = std::sin(m_phase) * *p<float>(peg_gain);
        m_phase += m_increment;
      }

      if (then < sample_count) {

        // Is the event a Note On?
        if (event[0] == 0x90) {
          int key = event[1];
          double frequency = 8.1758 * pow(2.0, key / 12.0);
          m_increment = m_invrate * 2 * M_PI * frequency;
        }

      }

      now = then;
      lv2midi_step(&midi);
    }

  }

protected:

  double m_phase;
  double m_increment;
  double m_invrate;

};


// For some reason the attribute part can only be in a prototype, not a
// function definition.
void initialise() __attribute__((constructor));
void initialise() {
  register_lv2<MyPlugin>(peg_uri);
}