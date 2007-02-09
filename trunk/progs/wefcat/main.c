// Waveform exchange file, file reader and parser. version 0.2
//
// Copyright 2006, BALLET Julien (ballet_j@epitech.net)
// This file is released under LGPL.
//

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wef_mem_0_2.h>

int			main(int ac, char **av)
{
  wfm		*t;
	int		bound;
	int 		i;

  if (ac > 1)
    {
      t = wef_open(av[1]);
      bound = t->wf_size;
      printf("%s\n", t->wf_name);
      printf("%s\n", t->wf_author);
      for (i = 0; i < bound; ++i)
        {
          printf("%d : %f\n", i, t->wf_wave[i]);
        }
    }
}
