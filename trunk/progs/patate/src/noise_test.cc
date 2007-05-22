/*
** noise_test.cc
** Login : <elthariel@elthariel-desktop>
** Started on  Sat May 19 11:36:10 2007 Nahlwe
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
#include <string>
#include "varinoise.hh"
#include "drumsynth.hh"

using namespace std;

int main(int ac, char **av)
{
  unsigned int  i;
  Dsp::DrumHat  h;
  string        s;
  float         *out = new float[128];
  float         *out2 = new float[128];
  float         **test = new float *[2];
  test[0] = out;
  test[1] = out2;
  //  float         **test2 = &test

  while (42)
    {
      cin >> s;
      h.note_on(1, 1);
      h.render(128, 44100, 1, test);
      for (i = 0; i < 128; i++)
        {
          cout << out[i] << endl;
          test[0][i] = 0.0;
          //          cout << test[0][i] << endl;
        }
    }
}
