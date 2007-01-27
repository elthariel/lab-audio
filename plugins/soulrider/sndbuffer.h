/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

//
// Class: nothing
//
// Created by: GESTES Cedric <goctaf@gmail.com>
// Created on: Sun Dec  3 19:34:17 2006
//
#ifndef _SNDBUFFER_H_
#define _SNDBUFFER_H_

#define SHORT_MAX 0x7FFF
/**
 * copy <sz> interlaced short into two output buffer
 */
void copys2ff(short *input, float *buffer_l, float *buffer_r, int sz);
void copys2f(short *input, float *buffer, int sz);
void copyf2ff(float *input, float *buffer_l, float *buffer_r, int sz);

#endif
