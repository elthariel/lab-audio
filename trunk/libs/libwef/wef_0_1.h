// Waveform exchange format, version 0.1
//
// Copyright 2006 Julien BALLET.
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

typedef struct		_waveform
{
	char[128]		wf_name;
		// Name of the waveforme (sine, square, ...)
	char[128]		wf_author;
		// Name of the author of this wf, or synth where it come from.
	unsigned int	wf_periods;
		// Number of periods in this waveform(s).
		//		generally 1. (for "graintable" like synthesis).
	unsigned int	wf_samples;		
		// Number of samples per periods of this waveform.
	double			wf_wave[];
		// 
}					waveform;

#ifdef __cplusplus
}
#endif

#endif