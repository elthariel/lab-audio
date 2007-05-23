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

#include "soundmap.h"

SoundMap::SoundMap()
  : m_buffer(NULL),
    m_read_position(0),
    m_write_position(0),
    m_size(0),
    m_allocated(0) {

}

SoundMap::~SoundMap() {
  if (m_buffer) {
    munmap(m_buffer, m_allocated);
    m_buffer = NULL;
  }
}

/** set the mmap size
 * later you wont need this
 */
void SoundMap::set_buffer_size(int samplecount) {
  if (m_buffer) {
    munmap(m_buffer, m_allocated);
    m_buffer = NULL;
  }
  m_buffer = (float *) mmap(0, samplecount*sizeof(float), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON, -1, 0);
}


/** seek into the mmap buffer
 *  move the read position
 */
int SoundMap::seek_read(int position) {
  m_read_position = position;
  return 0;
}


/** seek into the mmap buffer
 *  move the write position
 */
int SoundMap::seek_write(int position) {
  m_write_position = position;
  return 0;
}


/** read samples from the sound buffer
 *  this function move the seek position
 *  @return the current read position or -1 on error
 */
int SoundMap::get_samples(float *samples, int samplecount){
  int nb = 0;

  if (m_read_position + samplecount > m_allocated)
    nb = m_allocated - (m_read_position + samplecount);
  else
    nb = samplecount;
  nb = nb < 0 ? 0 : nb;
  copy(samples, m_buffer + m_read_position, nb);

  //verify if the region exist and is filled

  //update the region
  m_read_position += nb;
  return nb;
}

/** write samples into the sound buffer
 * @return the current write position or -1 on error
 */
int SoundMap::put_samples(float *samples, int samplecount) {
  int nb = 0;

  if (m_write_position + samplecount > m_allocated) {
    //allocate more baby
    return -1;
    nb = m_allocated - (m_read_position + samplecount);
  }
  else
    nb = samplecount;
  nb = nb < 0 ? 0 : nb;
  copy(m_buffer + m_write_position, samples, nb);
  m_write_position += nb;
  return nb;
}
