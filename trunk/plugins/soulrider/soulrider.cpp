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
#include "beatsmasher.h"
#include "../tronsonator/crossfader_curve.hpp"

/** This is the class that contains all the code and data for the plugin. */
class MyPlugin : public LV2Instrument {
public:

  /** The first parameter is the sample rate, the second is the path to the
      LV2 bundle, the third is the host features supported by this host. */
  MyPlugin(uint32_t rate, const char*, const LV2_Host_Feature**)
    : LV2Instrument(peg_n_ports),
    	m_ffmpeg(rate),
    	m_cue(0),
    	m_pause(false),
    	m_beatsmasher_l(rate),
    	m_beatsmasher_r(rate),
    	m_rate_tmp(0.),
    	m_fade_pos(0),
    	m_fade_curve(512*160)  {
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
		unsigned long pos = 0;
		float *dest_l = p<float>(peg_output_l);
		float *dest_r = p<float>(peg_output_r);

    while (now < sample_count) {
      then = uint32_t(lv2midi_get_event(&midi, &event_time, &event_size, &event));
      if (m_fade_pos < 160*512)
        m_ffmpeg.set_rate(*p(peg_pitch) + (m_rate_tmp - m_rate_tmp * m_fade_curve[m_fade_pos]));
      else
        m_ffmpeg.set_rate(*p(peg_pitch) + m_rate_tmp);
      if (then < sample_count)
				midi_event(event);
      if (!m_pause)
      	outsz = m_ffmpeg.process(dest_l, dest_r, (then - now));
      else
      	outsz = 0;
    	for (unsigned int i = outsz; i < (then - now); ++ i) {
				dest_l[i] = 0.;
				dest_r[i] = 0.;
			}
			m_fade_pos += then - now;
			m_beatsmasher_l.set_loop_size(*p(peg_beatsmasher_length));
			m_beatsmasher_r.set_loop_size(*p(peg_beatsmasher_length));
			m_beatsmasher_l.process(dest_l, then - now);
			m_beatsmasher_r.process(dest_r, then - now);
			dest_l += (then - now);
    	dest_r += (then - now);
      now = then;
      lv2midi_step(&midi);
    }
    pos = m_ffmpeg.get_pos();
    *p(peg_current_position) = (pos == 0 ? 0 : m_ffmpeg.get_length() / pos * 100.);
  }

  void midi_event(unsigned char *event) {
		int key = event[1];
		if (event[0] == 0x90) {
			switch(key) {
				case 64: internal_iplay(); break;
				case 62: pause(); break;
				case 63: cue(); break;
				case 42: play(); break;
				case 43: stop(); break;
			}
		}
		if (event[0] == 0x90 || event[0] == 0x80) {
			switch(key) {
				case 65: slowdown(event[0] == 0x90); break;
				case 66: slowup(event[0] == 0x90); break;
				case 67: beatsmasher(event[0] == 0x90); break;
			}
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
  	m_pause = false;
  	m_cue = 0;
  	m_ffmpeg.load_file(path);
  }

	/** play the track from cue
	 */
  void play() {
  	m_pause = false;
  	m_ffmpeg.seek(m_cue);
  }

  void internal_iplay() {
    m_ffmpeg.seek(m_ffmpeg.get_length() * (*p(peg_position) / 100.));
  }

  void pause() {
    m_pause = !m_pause;
  }

	/** cue the track
	 * set the cue point for later use
	 */
  void cue() {
  	m_cue = m_ffmpeg.get_pos();
  }
	/** stop the playback and rewind the file
	 */
	void stop() {
		m_pause = true;
		m_ffmpeg.seek(0);
	}

	void slowdown(bool noteon) {
		if (noteon) {
			m_rate_tmp = -0.3;
			m_fade_pos = 0;
		} else
			m_rate_tmp = 0.;
	}

	void slowup(bool noteon) {
		if (noteon) {
			m_rate_tmp = 0.3;
			m_fade_pos = 0;
		} else
			m_rate_tmp = 0.;
	}

	void beatsmasher(bool noteon) {
		m_beatsmasher_l.active(noteon);
		m_beatsmasher_r.active(noteon);
	}

protected:
  std::string m_filepath;
  ffmpeg m_ffmpeg;
  BeatSmasher m_beatsmasher_l;
  BeatSmasher m_beatsmasher_r;
  bool m_pause;
  unsigned long m_cue;
  unsigned long m_filelength;
  float m_rate_tmp;
  int m_fade_pos;
  CurveData m_fade_curve;
};


// For some reason the attribute part can only be in a prototype, not a
// function definition.
void initialise() __attribute__((constructor));
void initialise() {
  register_lv2_inst<MyPlugin>(peg_uri);
}
