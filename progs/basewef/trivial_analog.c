// Waveform exchange file Base waveform, version 0.2
//
// Copyright 2006, BALLET Julien (ballet_j@epitech.net)
// This file is released under GPL.
//

#include <stdlib.h>
#include "trivial_analog.h"

double			*square_gen(int *wavelen)
{
	int			i;
	double		*table;
	
	*wavelen = SQUARE_LEN;
	table = malloc(sizeof(double) * (*wavelen));
	for (i = 0; i < *wavelen; i++)
	{
		if (i > *wavelen / 2)
			table[i] = -1.0;
		else
			table[i] = 1.0;
	}
	
	return (table);
}

double			*saw_gen(int *wavelen)
{
	int			i;
	double		*table;
	
	*wavelen = SAW_LEN;
	table = malloc(sizeof(double) * (*wavelen));
	for (i = 0; i < *wavelen; i++)
	{
		table[i] = 1.0 - ((2.0 * i) / (*wavelen));
	}
	
	return (table);
}
