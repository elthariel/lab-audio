	/****************************************************************************

    myplugin.cpp - example file for writing LV2 plugins in C++

    Copyright (C) 2006  Lars Luthman <lars.luthman@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 01222-1307  USA

****************************************************************************/
//
// Class: BitSmasher
//
// Created by: GESTES Cedric <goctaf@gmail.com>
// Created on: Sun Dec  3 19:34:17 2006
//
#ifndef _BITSMASHER_H_
#define _BITSMASHER_H_

class BitSmasher {
	public:
		BitSmasher(int samplerate) {
			m_samplerate = samplerate;
			m_buffer = new float[samplerate];
			m_active = false;
			m_loop_size = 0;
			m_pos = 0;
		}
/**
 * name: inconnu
 * @param
 * @return
 */

/***
 *
 ***/
		void process(float *buffer, int samplecount) {
			int i = 0, j = 0;
			if (!m_active)
				return;
			while (j < samplecount)
			if (m_loadbuffer) {
				int ret = samplecount < m_loop_size - m_pos ? m_loop_size - m_pos : samplecount;
				for (m_pos; m_pos < ret; ++m_pos) {
					m_buffer[m_pos] = buffer[j];
					++j;
				}
			for (m_pos; m_pos < m_loop_size; ++m_pos) {
			}
		}

		inline void active(bool active) {
			m_active = active;
			if (m_active) {
				m_pos = 0;
				m_loadbuffer = true;
			}
		}

	private:
		float *m_buffer;
		int m_samplerate;
		int m_loop_size;
		float m_gate;
		bool m_loadbuffer;
		bool m_active;
		bool m_sync;

};

#endif
