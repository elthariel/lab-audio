// Waveform exchange file Base waveform, version 0.2
//
// Copyright 2006, BALLET Julien (ballet_j@epitech.net)
// This file is released under GPL.
//

#include <unistd.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "basewef_maker.h"

// FIXME put a zero at end of the strings.
wf						*wef_new(const char *name, const char *author)
{
	wf			*new_wef;
	
	new_wef = malloc(sizeof(wf));
	strncpy(new_wef->wf_author, author, 128);
	strncpy(new_wef->wf_name, name, 128);
	strncpy(new_wef->wf_magic, "Wef-0", 6);
	new_wef->wf_version = 1;
	new_wef->wf_grain_count = 0;
	return (new_wef);
}

void					wefmaker(const char *path, const char *name,
									const char *author, wave_gen_f gen)
{
	wf			*new_wef;
	double	*wave;
	int		wave_size;
	int		wfd;
	double 		tmp;
	int i;
	
	new_wef = wef_new(name, author);
	wave = (*gen)(&wave_size);
	for (i = 0; i < 200; i++)
		tmp = wave[i];
	new_wef->wf_size = wave_size;
	printf("Wave length %d\n", new_wef->wf_size);
	wfd = open(path, O_CREAT | O_WRONLY);
	if (!wfd)
		printf("Error opening %s\n", path);
	else
	{
		if (sizeof(wf) !=  write(wfd, (void *)new_wef, sizeof(wf)))
			printf ("Write error (header write) : %s", path);
		if ((sizeof(double) * wave_size) != write(wfd, (void *)wave, (sizeof(double) * wave_size)))
			printf ("Write error (wave write) : %s", path);
	}
	
	free(wave);
	free(new_wef);
}
