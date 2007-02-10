// Waveform exchange file Base waveform, version 0.2
//
// Copyright 2006, BALLET Julien (ballet_j@epitech.net)
// This file is released under GPL.
//

#include <stdlib.h>
#include <stdio.h>
#include "mymath.h"
#include "sin.h"
#include "math.h"

double			*sine_gen(int *wave_len)
{
	double		*sine_table;
	int			i;

	*wave_len = SINE_L;
	sine_table = malloc(sizeof(double) * SINE_L);
	for (i = 0; i < (*wave_len); i++)
	{
		sine_table[i] = sine((2.0 * M_PI * (double)i) / *wave_len, SINE_ITER);
		//sine_table[i] = sin((2.0 * M_PI * (double)i) / ((double) SINE_L));
	}
	return (sine_table);
}
