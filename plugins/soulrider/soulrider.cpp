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
#include <iostream>
#include "lv2instrument.hpp"
#include "lv2plugin.hpp"
#include "lv2-miditype.h"
#include "lv2-midifunctions.h"
#include "soulrider.peg"
#include "ffmpeginterface.h"

/** This is the class that contains all the code and data for the plugin. */
class MyPlugin : public LV2Instrument {
public:

  /** The first parameter is the sample rate, the second is the path to the
      LV2 bundle, the third is the host features supported by this host. */
  MyPlugin(uint32_t rate, const char*, const LV2_Host_Feature**)
    : LV2Instrument(peg_n_ports),
    	m_ffmpeg(rate) {
		m_pause = false;
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
		uint32_t outsz = 0;
		float *dest_l = p<float>(peg_output_l);
		float *dest_r = p<float>(peg_output_r);


    while (now < sample_count) {
      then = uint32_t(lv2midi_get_event(&midi, &event_time, &event_size, &event));
      m_ffmpeg.set_rate(*p(peg_pitch));

//      m_ffmpeg.process(p<float>(peg_output_l), p<float>(peg_output_r), (then - now));


      if (then < sample_count) {
        // Is the event a Note On?
        if (event[0] == 0x90) {
          int key = event[1];
          switch(key) {
          	case 62: pause();
          		m_pause = !m_pause;
          		break;
          	case 63: cue(); break;
          	case 42: play(); break;
          }
        }
      }
      if (m_pause)
      	outsz = 0;
      else
      	outsz = m_ffmpeg.soundtouch(dest_l, dest_r, (then - now));
    	for (int i = outsz; i < (then - now); ++ i) {
				dest_l[i] = 0.;
				dest_r[i] = 0.;
			}
			dest_l += (then - now);
    	dest_r += (then - now);
      now = then;
      lv2midi_step(&midi);
    }
  }

    /** Arbitrary configuration function without RT constraints. */
  char* configure(const char* key, const char* value) {
  	return 0;
  }

  /** Function for loading data from external files. */
  char* set_file(const char* key, const char* filename) {
  	m_ffmpeg.load_file(filename);
  	return 0;
  }


  void load_file(const std::string& path) {
  	m_ffmpeg.load_file(path);
  }

  void pause() {
  }

  void play() {
  }

  void cue() {
  }



protected:
  std::string m_filepath;
  ffmpeg m_ffmpeg;
  bool m_pause;
};


// For some reason the attribute part can only be in a prototype, not a
// function definition.
void initialise() __attribute__((constructor));
void initialise() {
  register_lv2_inst<MyPlugin>(peg_uri);
}