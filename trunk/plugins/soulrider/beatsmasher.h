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
// Created by: GESTES Cedric <ctaf42@gmail.com>
// Created on: Mon Jan  29 19:34:17 2007
//
#ifndef _BEATSMASHER_H_
#define _BEATSMASHER_H_

class BeatSmasher {
public:
	BeatSmasher(int samplerate);

	/** process a mono buffer
	 */
	void process(float *buffer,const int samplecount);

	/** toggle the beatsmasher on and off
	 */
	void active(const bool active);
	inline void set_loop_size(int loop_size) { m_loop_size = loop_size; }

protected:
	void learn(float *buffer, const int samplecount);

private:
	float *m_buffer;						///beatsmasher buffer
	int m_samplerate;						///the samplerate of the buffer
	int m_loop_size;						///the length in buffer of the loop
	int m_pos;									///the current position in the buffer (reading)
	int m_pos_learn;						///the current position in the buffer (writing)
	float m_gate;								///unused
	bool m_loadbuffer;					///writing or reading the buffer?
	bool m_active;							///is the beatsmasher active?
	bool m_sync;								///unused
};

#endif
