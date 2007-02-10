// Waveform exchange file Base waveform, version 0.2
//
// Copyright 2006, BALLET Julien (ballet_j@epitech.net)
// This file is released under GPL.
//

#define	SQUARE_LEN      1024
#define	SAW_LEN			    4096
#define EXP_LEN         4096
#define EXP10_LEN       4096

double          *square_gen(int *);
double          *saw_gen(int *);
double          *exp_gen(int *);
double          *exp10_gen(int *);
