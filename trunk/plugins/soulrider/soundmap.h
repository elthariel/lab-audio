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
// Class: SoundMap
//
// Created by: GESTES Cedric <ctaf42@gmail.com>
// Created on: Mon Jan  29 19:34:17 2007
//
#ifndef __SOUNDMAP_H__
#define __SOUNDMAP_H__

#include "sys/mman.h"
/*** represent a sound buffer in memory using mmap
 * you should have only one thread that read
 * and one thread that write
 */
class SoundMap {
public:
	SoundMap();
	~SoundMap();

	/** reset the buffer, set the mmap size
	 * later it wont need this
	 */
	void set_buffer_size(int samplecount);

	/** write samples into the sound buffer
	 * @return the current write position or -1 on error
	 */
	int put_samples(float *samples, int samplecount);

	/** seek into the mmap buffer
	 *  move the read position
	 */
	int seek_read(int position);

	/** seek into the mmap buffer
	 *  move the write position
	 */
	int seek_write(int position);

	/** read samples from the sound buffer
	 *  this function move the seek position
	 *  @return the current read position or -1 on error
	 */
	int get_samples(float *samples, int samplecount);

private:
	int m_read_position;
	int m_write_position;
	int m_size;///needed?
	int m_allocated;///the allocated size of the buffer
	int grow_size;///the size the buffer grow by
	float *m_buffer;
///mmap
};

#endif
