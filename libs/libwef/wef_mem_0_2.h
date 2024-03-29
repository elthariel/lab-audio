// Waveform exchange file, memory representation. version 0.2
//
// Copyright 2006, BALLET Julien (ballet_j@epitech.net)
// This file is released under LGPL. (Lesser General Public License, see www.fsf.org)
//

#ifndef WEF_MEM_H_
# define WEF_MEM_H_

# include "wef_file_0_2.h"

# ifdef __cplusplus
extern "C"
{
# endif

  typedef struct		_wfm
  {
    unsigned char	wf_version;
    char		*wf_magic;
    char		*wf_name;
    char		*wf_author;
    uint32		wf_grain_count;
    uint32		wf_size;
    wf			*wf_file;
    grain		*wf_grain_index;
    double		*wf_wave;
  }				wfm;

  /*
  ** Read functions.
  */
  // Exported
  wfm             *wef_open(const char *path);
  void            wef_close(wfm *tofree);

  // Internals
  int             wef_preopen(const char *path, wf *wef_file);
  wf              *wef_read(int fd, wf *wef_file);
  void            wfm_fill(wfm *wef_mem, wf *wef_file);

# ifdef __cplusplus
}
# endif
#endif
