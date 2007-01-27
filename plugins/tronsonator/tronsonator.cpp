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
#include "crossfader_curve.hpp"

/** This is the class that contains all the code and data for the
    plugin. */
class MyPlugin : public LV2Plugin {
public:

  /** The first parameter is the sample rate, the second is the path
      to the LV2 bundle, the third is the host features supported by
      this host. */
  MyPlugin(uint32_t rate, const char*, const LV2_Host_Feature**)
    : LV2Plugin(peg_n_ports), m_cross(256) {
  }


  class StepFunc {
    //step cant be changed at runtime, cause we wont want malloc when
    //processing
    StepFunc(int step) {
      m_step = step;
      //default init
      m_tab = (double *)malloc(sizeof(double) * m_step);
      for (int i = 0; i < m_step; ++i) {
        m_tab[i] = (double)i / (double)m_step;
      }
    }
    /* input = [ 0.0 - 1.0 ]
     * output = euhh
     * yes, this is an outrageous cast!
     */
    inline double get_value(double value)const {
      return m_tab[(int)value * m_step];
    }

    inline void set_value(int step, double value) {
      m_tab[step] = value;
    }

    inline int get_step_count()const {
      return m_step;
    }

  private:
    int m_step;
    double *m_tab;
  };

  float crossfade(float cross, float left, float right) {
    /*
    float cross_l = cross <= 0.5 ? 1.0 : 1.0 - (cross * 2.0 - 1.0);
    float cross_r = cross >= 0.5 ? 1.0 : (cross * 2.0);*/
    //return left * StepFunc(cross_l) + right * StepFunc(cross_r);
    float cross_l = m_cross[((uint32_t) (cross * 512)];
    float cross_r = m_cross[512 - ((uint32_t) cross * 512)];
    return left * cross_l + right * cross_r;
  }


  /** The run() callback. This is the function that gets called by the
      host when it wants to run the plugin. The parameter is the
      number of sample frames to process. */
  void run(uint32_t sample_count) {
    float cross1l, cross1r, cross2l, cross2r;
    while (sample_count) {
			cross1l = 0.0;
      cross1r = 0.0;
      cross2l = 0.0;
      cross2r = 0.0;
      if (*p(peg_crossfader_ch_1) == 1) {
        cross1l += p(peg_input_l1)[sample_count] * *p(peg_gain_1) * *p(peg_volume_1);
        cross1r += p(peg_input_r1)[sample_count] * *p(peg_gain_1) * *p(peg_volume_1);
      } else if (*p(peg_crossfader_ch_1) == 2) {
        cross2l += p(peg_input_l1)[sample_count] * *p(peg_gain_1) * *p(peg_volume_1);
        cross2r += p(peg_input_r1)[sample_count] * *p(peg_gain_1) * *p(peg_volume_1);
      }
      if (*p(peg_crossfader_ch_2) == 1) {
        cross1l += p(peg_input_l2)[sample_count] * *p(peg_gain_2) * *p(peg_volume_2);
        cross1r += p(peg_input_r2)[sample_count] * *p(peg_gain_2) * *p(peg_volume_2);
      } else if (*p(peg_crossfader_ch_2) == 2) {
        cross2l += p(peg_input_l2)[sample_count] * *p(peg_gain_2) * *p(peg_volume_2);
        cross2r += p(peg_input_r2)[sample_count] * *p(peg_gain_2) * *p(peg_volume_2);
      }
      if (*p(peg_crossfader_ch_3) == 1) {
        cross1l += p(peg_input_l3)[sample_count] * *p(peg_gain_3) * *p(peg_volume_3);
        cross1r += p(peg_input_r3)[sample_count] * *p(peg_gain_3) * *p(peg_volume_3);
      } else if (*p(peg_crossfader_ch_3) == 2) {
        cross2l += p(peg_input_l3)[sample_count] * *p(peg_gain_3) * *p(peg_volume_3);
        cross2r += p(peg_input_r3)[sample_count] * *p(peg_gain_3) * *p(peg_volume_3);
      }
      if (*p(peg_crossfader_ch_4) == 1) {
        cross1l += p(peg_input_l4)[sample_count] * *p(peg_gain_4) * *p(peg_volume_4);
        cross1r += p(peg_input_r4)[sample_count] * *p(peg_gain_4) * *p(peg_volume_4);
      } else if (*p(peg_crossfader_ch_4) == 2) {
        cross2l += p(peg_input_l4)[sample_count] * *p(peg_gain_4) * *p(peg_volume_4);
        cross2r += p(peg_input_r4)[sample_count] * *p(peg_gain_4) * *p(peg_volume_4);
      }
      p(peg_output_l)[sample_count] = crossfade(*p(peg_crossfader), cross1l, cross2l);
      p(peg_output_r)[sample_count] = crossfade(*p(peg_crossfader), cross1r, cross2r);

      p(peg_headphone_l)[sample_count] = 0.;
			p(peg_headphone_r)[sample_count] = 0.;
			if (*p(peg_headphone_1)) {
				p(peg_headphone_l)[sample_count] = p(peg_input_l1)[sample_count] * *p(peg_gain_1);
				p(peg_headphone_r)[sample_count] = p(peg_input_r1)[sample_count] * *p(peg_gain_1);
			}
			if (*p(peg_headphone_2)) {
				p(peg_headphone_l)[sample_count] += p(peg_input_l2)[sample_count] * *p(peg_gain_2);
				p(peg_headphone_r)[sample_count] += p(peg_input_r2)[sample_count] * *p(peg_gain_2);
			}
			if (*p(peg_headphone_3)) {
				p(peg_headphone_l)[sample_count] += p(peg_input_l3)[sample_count] * *p(peg_gain_3);
				p(peg_headphone_r)[sample_count] += p(peg_input_r3)[sample_count] * *p(peg_gain_3);
			}
			if (*p(peg_headphone_4)) {
				p(peg_headphone_l)[sample_count] += p(peg_input_l4)[sample_count] * *p(peg_gain_4);
				p(peg_headphone_r)[sample_count] += p(peg_input_r4)[sample_count] * *p(peg_gain_4);
			}

		  sample_count--;
		}
  }

protected:

  crossdata             m_cross;
};


// For some reason the attribute part can only be in a prototype, not
// a function definition.
void initialise() __attribute__((constructor));
void initialise() {
  register_lv2<MyPlugin>(peg_uri);
}
