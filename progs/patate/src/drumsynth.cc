/*
** drumsynth.cc
** Login : <elthariel@elthariel-desktop>
** Started on  Thu May 17 18:17:17 2007 Nahlwe
** $Id$
**
** Copyright (C) 2007 Nahlwe
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#include <iostream>
#include "drumsynth.hh"

using namespace std;

/*
 * DrumHat class
 */
namespace Dsp
{
  DrumHat::DrumHat()
    : m_noise(*new iOscVectorAdapter(*new WhiteNoise(*new URandom))),
      m_gate(false)
  {
  }

  void            DrumHat::note_on(char note, char vel)
  {
    //    cout << "Played a noise" << endl;
    m_gate = true;

  }

  void            DrumHat::note_off(char note, char vel)
  {
    //    cout << "Stopped a noise" << endl;
    m_gate = false;
  }

  void            DrumHat::cc(unsigned int control, float value)
  {
  }

  void            DrumHat::render(unsigned int sample_count,
                                  unsigned int sample_rate,
                                  unsigned int channel_count,
                                  sample_t **out)
  {
    unsigned int i, j;

    if (m_gate)
      {
        m_noise.render(out[0], sample_count);
        for (j = 1; j < channel_count; j++)
          for (i = 0; i < sample_count; i++)
            out[j][i] += out[0][i];
      }
  }

  void            DrumHat::reset()
  {
    m_gate = false;
  }

};

