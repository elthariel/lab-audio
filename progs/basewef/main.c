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
	wefmaker("sin.wef", "mySine - 4096",
				"Elthariel", &sine_gen); 
	wefmaker("wefs/saw.wef", "mySaw - trivial generation - 4096",
				"Elthariel", &saw_gen);
	wefmaker("wefs/square.wef", "mySquare - trivial generation - 1024",
				"Elthariel", &square_gen);
	system("PAUSE");
	return 0;
}
