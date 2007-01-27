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
// Class: ffmpeg
//
// Created by: GESTES Cedric <goctaf@gmail.com>
// Created on: Sun Dec  3 19:34:17 2006
//
#ifndef _FFMPEG_INTERFACE_H_
#define _FFMPEG_INTERFACE_H_

#include <ffmpeg/avcodec.h>
#include <ffmpeg/avformat.h>
#include <gtkmm.h>
#define FLOAT_SAMPLES
#include "soundtouch/SoundTouch.h"

class ffmpeg {
public:
	ffmpeg(unsigned int samplerate = 44100);
	static void ffmpeg_init();
	
  void close();
  //load an mp3 and reset all variable
	bool load_file(const Glib::ustring &str);

	//return the length in sec
	int get_sec_length();

	//return the pos in sec
	int get_sec_pos();

	//return the length of the song
	int get_length();

  //return the current pos in the song
	int get_pos();

  //seek
	bool seek(unsigned long long seek_pos);

  //process the buffer, update pos
  //return true, if its the last buffer, feel with 0
	//int process(float *buffer_l, float *buffer_r, int samplecount);
//	int process(float *buffer, int samplecount);
//	int process_mono(float *buffer, int samplecount);
	inline void set_rate(float rate) { m_soundtouch.setRate(rate); }
	inline void set_pitch(float pitch) { m_soundtouch.setPitch(pitch); }
	int process(float *buffer_l, float *buffer_r, int samplecount);
protected:
  //read one paquet from ffmpeg
	bool readpacket();
	bool streadpacket(int octetoffset = 0);
	//void copy(char *input, char *buffer_l, char *buffer_r, int sz);

private:
	int m_channels;
	bool m_loaded;
	unsigned long m_filelength;	/// in number of short for one raw file (left and right)
	unsigned long m_pos;
	unsigned int m_samplerate;
	AVFormatContext *m_formatctx;
  AVInputFormat *m_iformat;
	int m_audiostream;
	AVCodecContext *m_codecctx;
	AVCodec *m_codec;
	AVFrame *m_frame;
	AVPacket m_packet;
	volatile int m_bufferoffset;
  volatile int m_buffersize;
  short m_buffer[AVCODEC_MAX_AUDIO_FRAME_SIZE];
  float m_buffer2[AVCODEC_MAX_AUDIO_FRAME_SIZE];
  float m_outbuffer[AVCODEC_MAX_AUDIO_FRAME_SIZE];
  soundtouch::SoundTouch m_soundtouch;
};


#endif
