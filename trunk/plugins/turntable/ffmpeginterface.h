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

class ffmpeg {
public:
  ffmpeg();
	static void ffmpeg_init();

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
  bool process(float *buffer_l, float *buffer_r, int samplecount);

private:
	int channels;
	unsigned long filelength;
	AVFormatContext *pFormatCtx;
  AVInputFormat *iformat;
	int audioStream;
	AVCodecContext *pCodecCtx;
	AVCodec *pCodec;
	AVFrame *pFrame;
	AVPacket packet;
	volatile int bufferOffset;
  volatile int bufferSize;
  double buffer[AVCODEC_MAX_AUDIO_FRAME_SIZE];
};


#endif
