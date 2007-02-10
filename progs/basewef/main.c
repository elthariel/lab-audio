// Waveform exchange file Base waveform, version 0.2
//
// Copyright 2006, BALLET Julien (ballet_j@epitech.net)
// This file is released under GPL.
//

#include <stdio.h>
#include <stdlib.h>
#include "basewef_maker.h"
#include "trivial_analog.h"
#include "sin.h"

int main(int argc, char *argv[])
{
	wefmaker("wefs/sin.wef", "mySine - 4096\n",
				"Elthariel", &sine_gen);
	wefmaker("wefs/saw.wef", "mySaw - trivial generation - 4096n",
				"Elthariel", &saw_gen);
	wefmaker("wefs/square.wef", "mySquare - trivial generation - 1024\n",
				"Elthariel", &square_gen);
  wefmaker("wefs/exp.wef", "Exp base e", "Elthariel", &exp_gen);
  wefmaker("wefs/exp10.wef", "Exp base 10", "Elthariel", &exp10_gen);
	return 0;
}
