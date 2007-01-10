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
#include <iostream>
#include "ffmpeginterface.h"

static bool ffmpeginit = false;

void ffmpeg::ffmpeg_init()
{
	if (!ffmpeginit) {
		av_register_all();
		ffmpeginit = true;
	}
}

ffmpeg::ffmpeg() {
	m_packet.data = NULL;
	m_frame = NULL;
	m_codecctx = NULL;
	m_formatctx = NULL;
}

bool ffmpeg::load_file(const Glib::ustring &str) {
	AVFormatParameters param;

  if (m_packet.data != NULL)
  	av_free_packet(&m_packet);
	m_packet.data = NULL;
	m_bufferoffset = 0;
	m_buffersize = 0;
	memset(m_buffer, 0, AVCODEC_MAX_AUDIO_FRAME_SIZE);
	ffmpeg_init();

	/* initialize param to something so av_open_input_file works for raw */
	memset(&param, 0, sizeof(AVFormatParameters));
	param.channels = 2;
	param.sample_rate = 44100;

	m_iformat = av_find_input_format(str.c_str());
	// Open audio file
	if(av_open_input_file(&m_formatctx, str.c_str(), m_iformat, 0, &param)!=0) {
		std::cerr << "av_open_input_file: cannot open" << str << std::endl;
		return false;
		}

	// Retrieve stream information
	if(av_find_stream_info(m_formatctx)<0) {
		std::cerr << "av_find_stream_info: cannot open " << str << std::endl;
		return false;
	}

	//debug only
	dump_format(m_formatctx, 0, str.c_str(), false);

	// Find the first video stream
	m_audiostream=-1;
	for(int i=0; i<m_formatctx->nb_streams; i++)
		if(m_formatctx->streams[i]->codec->codec_type == CODEC_TYPE_AUDIO) {
			m_audiostream = i;
			break;
		}
	if(m_audiostream == -1) {
		std::cerr << "cannot find an audio stream: cannot open" << str << std::endl;
		return false;
	}

	// Get a pointer to the codec context for the video stream
	m_codecctx=m_formatctx->streams[m_audiostream]->codec;

	// Find the decoder for the audio stream
	if(!(m_codec=avcodec_find_decoder(m_codecctx->codec_id))) {
		std::cerr << "cannot find a decoder for " << str << std::endl;
		return false;
	}

	//avcodec_open is not thread safe
//		lock();
	if(avcodec_open(m_codecctx, m_codec)<0) {
		std::cerr << "avcodec: cannot open " << str << std::endl;
		return false;
	}
//		unlock();

	m_frame=avcodec_alloc_frame();
	m_channels = m_codecctx->channels;

	if(m_channels > 2){
		std::cerr << "ffmpeg: No support for more than 2 channels!" << std::endl;
		return false;
	}
}

void ffmpeg::close() {
	if (m_frame)
	  av_free(m_frame);

	// Close the codec
	//lock();
	if (m_codecctx)
	  avcodec_close(m_codecctx);
	//unlock();

	// Close the file
	if (m_formatctx)
	  av_close_input_file(m_formatctx);
}

int ffmpeg::get_length() {
}

int ffmpeg::get_pos() {
}

bool ffmpeg::seek(unsigned long long seek_pos) {
}

int ffmpeg::process(float *buffer_l, float *buffer_r, int samplecount) {
	char *dest = (char *) destination;
	char *src = NULL;
	int index = 0;
	int outsize = 0;
	int needed = samplecount*2;//*channels;

	//copy previous buffer
	src = (char *)m_buffer;
	src += m_bufferoffset;
	while (needed > 0) {
		if (m_bufferoffset < m_buffersize) {
			index = m_buffersize - m_bufferoffset > needed ? needed : m_buffersize - m_bufferoffset;
			memcpy((char *)dest, (char *)(src), index);
			src += index;
			dest += index;
			needed -= index;
			m_bufferoffset += index;
			outsize += index;
		}
		if (needed > 0 && (m_buffersize - m_bufferoffset <= 0)) {
			m_bufferoffset = 0;
			readpaquet();
			src = (char*)m_buffer;
			src += m_bufferoffset;
		}
	}
	return (outsize/2);
}


bool ffmpeg::readpaquet(){
	char *dst;
	unsigned char *src;
	int ret = 0;
	int readsize = 0;
	int inputsize = 0;
	int tries = 0;

	//DEBUG
	m_buffersize = 0;
	m_bufferoffset = 0;
	//memset(buffer, 0, AVCODEC_MAX_AUDIO_FRAME_SIZE);
	while (av_read_packet(m_formatctx, &m_packet)>0) {
		if (m_packet.stream_index==m_audiostream) {
			dst = (char *)m_buffer;
			src = m_packet.data;
			inputsize = 0;
			readsize = 0;
			tries = 0;
			do {
				ret = avcodec_decode_audio(m_codecctx, (int16_t *)dst, &readsize, src, m_packet.size - inputsize);
				if (readsize == 0) {
					//tries++;
					break;
				}
				if (ret <= 0) {
					tries++;
  				if (tries > 3) break;
	  				continue;
				}
				dst += readsize;
				m_buffersize += readsize;
				src += ret;
				inputsize += ret;
			} while (inputsize < m_packet.size);
			if (m_buffersize != 0)
				return true;
		}
		av_free_packet(&m_packet);
	}
	return false;
}