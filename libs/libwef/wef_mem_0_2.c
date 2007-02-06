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
#include "wef_mem_0_2.h"

int32			wef_preopen(const char *path, wf *wef_file)
{
	int				fd;
	unsigned int	read_sz;

	fd = open(path, O_RDONLY | O_BINARY );
	if (fd)
	{
		read_sz = read(fd, (void *)wef_file, sizeof(wf));  //FIXME Ptential bug here sizeof - 1
		if (read_sz != (sizeof(wf)))
		{
			printf("Error reading %s, File header corruption\n", path);
			close(fd);
			fd = 0;
		}
	}
	else
		printf("Error opening %s\n", path);
	return (fd);
}




wf				*wef_read(int32 fd, wf *wef_file)
{
	int			read_size;
	wf				*wef_file_full;
	int			wef_size;
	int			tmp;
	
	wef_size = sizeof(wf) + sizeof(grain) * wef_file->wf_grain_count 
			+ sizeof(double) * wef_file->wf_size;	 //FIXME correct size (-1 ?)
	read_size = wef_size - sizeof(wf);
	wef_file_full = (wf *)malloc(wef_size);
	memcpy((void *)wef_file_full, (void *)wef_file, sizeof(wf));
	tmp = read(fd, ((void *) wef_file_full) + sizeof(wf), read_size);
	if (read_size != tmp)
	{
		printf("Read problem : %s", wef_file->wf_name);
		free(wef_file_full);
		wef_file_full = 0;
	}
	return (wef_file_full);	
}




void			wfm_fill(wfm *wef_mem, wf *wef_file)
{
	wef_mem->wf_version = wef_file->wf_version;
	wef_mem->wf_magic = wef_file->wf_magic;
	wef_mem->wf_name = wef_file->wf_name;
	wef_mem->wf_author = wef_file->wf_author;
	wef_mem->wf_grain_count = wef_file->wf_grain_count;
	wef_mem->wf_size = wef_file->wf_size;
	wef_mem->wf_file = wef_file;
	wef_mem->wf_grain_index = (grain *) wef_file->wf_content;
	wef_mem->wf_wave = (double *) (wef_file->wf_content + wef_file->wf_grain_count * sizeof(grain));
}





wfm			*wef_open(const char *path)
{
	int			fd;
	wf				wef_file;
	wf				*wef_file_full;
	wfm			*wef_mem;

	fd = wef_preopen(path, &wef_file);
	if (fd)
	{
		wef_mem = (wfm *) malloc(sizeof(wfm));
		wef_file_full = wef_read(fd, &wef_file);
		if (!wef_file_full)
		{
			free (wef_mem);
			return (0);
		}
		wfm_fill(wef_mem, wef_file_full);
		return (wef_mem);
	}
	else
		return (0);
}

void			wef_close(wfm *tofree)
{
	free(tofree->wf_file);
	free(tofree);
}


int			main()
{
	wfm		*t;
	int		bound;
	int 		i;
	
	t = wef_open("..\\basewef\\wefs\\sin.wef");
	bound = t->wf_size;
	for (i =0; i < bound; ++i)
		{ 
			printf("%d : %f\n", i, t->wf_wave[i]);
			if (!(i % 500))
				system("PAUSE");
		}
	system("PAUSE");
}

