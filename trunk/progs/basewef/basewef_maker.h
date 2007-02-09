// Waveform exchange file Base waveform, version 0.2
//
// Copyright 2006, BALLET Julien (ballet_j@epitech.net)
// This file is released under GPL.
//

#ifndef BASEWEF_MAKER_H_
# define BASEWEF_MAKER_H_

#include <wef_file_0_2.h>

typedef double		*(*wave_gen_f)(int *wave_len);

wf						*wef_new(const char *name, const char *author);
void					wefmaker(const char *path, const char *name,
									const char *author, wave_gen_f gen);

#endif
