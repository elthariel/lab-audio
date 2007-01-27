//
// Class: nothing
//
// Created by: GESTES Cedric <goctaf@gmail.com>
// Created on: Sun Dec  3 19:34:17 2006
//
#include "sndbuffer.h"

// copy a tab of short (interlaced)
//  to two tab of float

void copys2ff(short *input, float *buffer_l, float *buffer_r, int sz) {
  int j = 0,k = 0;
  float res;

  for (int i = 0; i < sz; ++i) {
  	if (i % 2) {
  	  buffer_r[j] = input[i];
  	  buffer_r[j] /= (float)SHORT_MAX;
  	  ++j;
  	} else {
  	  buffer_l[k] = input[i];
  	  buffer_l[k] /= (float)SHORT_MAX;
  	  ++k;
  	}
  }
}

void copys2f(short *input, float *buffer, int sz) {
  for (int i = 0; i < sz; ++i) {
  	buffer[i] = input[i];
  	buffer[i] /= (float)SHORT_MAX;
  }
}

void copyf2ff(float *input, float *buffer_l, float *buffer_r, int sz) {
  int j = 0,k = 0;

  for (int i = 0; i < sz; ++i) {
  	if (i % 2) {
  	  buffer_r[j] = input[i];
  	  ++j;
  	} else {
  	  buffer_l[k] = input[i];
  	  ++k;
  	}
  }
}
