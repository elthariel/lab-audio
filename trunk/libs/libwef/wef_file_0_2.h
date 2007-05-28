// Waveform exchange file format, version 0.2
//
// Copyright 2006, BALLET Julien (ballet_j@epitech.net)
// This file is released under LGPL.
//

//This is a try for defining a standard format for exchanging waveforms
//between software synthetizer which are using precomputed waveforms.
//(.ie not realtime synthetized) This will allow to easily extand softsynths
//that supports this format, and to separate the processes of synthetizing
//(band-limited) waveforms and writing other synths features.
//
//This format supports waveforms for either simple wavetable synthesis and
//graintable synthesis. Simples waveforms have only one period, graintable
//could have plenty of them.

#ifndef WEF_H_
# define WEF_H_

#ifdef __cplusplus	// C++ compiler compatibility
extern "C"
{
#endif

# include <stdint.h>
  typedef	uint32_t uint32;
  typedef	uint64_t uint64;

  typedef struct          _grain
  {
    uint32			grain_size;
		// Size of this grain (in samples).
    uint32			grain_pos;
		// Grain position offset (in 'sample size', ie 8 bytes),
		//		relative to the start of the graintable data (.ie after grain index).
  }                       grain;

# define WEF_MAGIC_LEN  6
# define WEF_NAME_LEN   128
# define WEF_AUTHOR_LEN 128

  typedef struct          _wf
  {
    unsigned char	wf_version;
		// = 1;
    char				wf_magic[6];
		// = "Wef-0";
    char				wf_name[128];
		// Name of the waveforme (sine, square, ...)
    char				wf_author[128];
		// Name of the author of this wf, or synth where it come from.
    uint32			wf_grain_count;
		// Number of grains in the grain index. 0 (or 1) if none (monoperiod).
    uint32			wf_size;
		// Size of wf_content in byte. size of the waveform if simple waveform (monoperiod/not graintable).
    char				wf_content[];
		// Contain optional grain index, and the waveform data.
    //(Waveform data are stored as double precision floats).
  }                       wf;

  //Grain index (if any) is found at the beginning of wf_content.
  //Waveform data can be found at :
  //	wf_data_pos = &wf_content + (wf_grain_count * sizeof(grain));
  //Waveform data is double precision floaating point number, stored using x86 way (big endian).

#ifdef __cplusplus
}
#endif

#endif
