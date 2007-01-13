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
//#include "lv2instrument.hpp"
#include "lv2plugin.hpp"
#include "lv2-miditype.h"
#include "lv2-midifunctions.h"
#include "tronsonator.peg"

/** This is the class that contains all the code and data for the plugin. */
class MyPlugin : public LV2Plugin {
public:

  /** The first parameter is the sample rate, the second is the path to the
      LV2 bundle, the third is the host features supported by this host. */
  MyPlugin(uint32_t rate, const char*, const LV2_Host_Feature**)
    : LV2Plugin(peg_n_ports) {

  }

  /** The run() callback. This is the function that gets called by the host
      when it wants to run the plugin. The parameter is the number of sample
      frames to process. */
  void run(uint32_t sample_count) {
		while (sample_count) {
			p<float>(peg_output_l)[sample_count] = p<float>(peg_input_l1)[sample_count] +
																						 p<float>(peg_input_l2)[sample_count] +
																						 p<float>(peg_input_l3)[sample_count] +
																						 p<float>(peg_input_l4)[sample_count];
			p<float>(peg_output_r)[sample_count] = p<float>(peg_input_r1)[sample_count] +
																						 p<float>(peg_input_r2)[sample_count] +
																						 p<float>(peg_input_r3)[sample_count] +
																						 p<float>(peg_input_r4)[sample_count];
			if (p<bool>(peg_headphone_1)) {
				p<float>(peg_headphone_l)[sample_count] = p<float>(peg_input_l1)[sample_count];
				p<float>(peg_headphone_r)[sample_count] = p<float>(peg_input_r1)[sample_count];
			}
			if (p<bool>(peg_headphone_2)) {
				p<float>(peg_headphone_l)[sample_count] += p<float>(peg_input_l2)[sample_count];
				p<float>(peg_headphone_r)[sample_count] += p<float>(peg_input_r2)[sample_count];
			}
			if (p<bool>(peg_headphone_3)) {
				p<float>(peg_headphone_l)[sample_count] += p<float>(peg_input_l3)[sample_count];
				p<float>(peg_headphone_r)[sample_count] += p<float>(peg_input_r3)[sample_count];
			}
			if (p<bool>(peg_headphone_4)) {
				p<float>(peg_headphone_l)[sample_count] += p<float>(peg_input_l4)[sample_count];
				p<float>(peg_headphone_r)[sample_count] += p<float>(peg_input_r4)[sample_count];
			}

		  sample_count--;
		}
  }

protected:

};


// For some reason the attribute part can only be in a prototype, not a
// function definition.
void initialise() __attribute__((constructor));
void initialise() {
  register_lv2<MyPlugin>(peg_uri);
}
