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

#include "ffmpeginterface.h"

static bool ffmpeginit = false;
static void ffmpeg::ffmpeg_init()
{
	if (!ffmpeginit) {
		av_register_all();
		av_log_set_callback(LibavcodecCallback);
		ffmpeginit = true;
	}
}


bool ffmpeg::load_file(const Glib::ustring &str) {
	int            i;
	AVFormatParameters param;

	packet.data = NULL;
	bufferOffset = 0;
	bufferSize = 0;
	memset(buffer, 0, AVCODEC_MAX_AUDIO_FRAME_SIZE);
	FFmpegInit();

	/* initialize param to something so av_open_input_file works for raw */
	memset(&param, 0, sizeof(AVFormatParameters));
	param.channels = 2;
	param.sample_rate = 44100;

	iformat = av_find_input_format(fname);
	// Open audio file
	if(av_open_input_file(&pFormatCtx, fname, iformat, 0, &param)!=0) {
		std::cout << "av_open_input_file: cannot open" << fname << std::endl;
		return;
		}

	// Retrieve stream information
	if(av_find_stream_info(pFormatCtx)<0) {
		std::cout << "av_find_stream_info: cannot open " << fname << std::endl;
		return;
	}

	//debug only
	dump_format(pFormatCtx, 0, fname, false);

	// Find the first video stream
	audioStream=-1;
	for(i=0; i<pFormatCtx->nb_streams; i++)
		if(pFormatCtx->streams[i]->codec->codec_type==CODEC_TYPE_AUDIO) {
			audioStream=i;
			break;
		}
	if(audioStream==-1) {
		std::cout << "cannot find an audio stream: cannot open" << fname << std::endl;
		return;
	}

	// Get a pointer to the codec context for the video stream
	pCodecCtx=pFormatCtx->streams[audioStream]->codec;

	// Find the decoder for the audio stream
	if(!(pCodec=avcodec_find_decoder(pCodecCtx->codec_id))) {
		std::cout << "cannot find a decoder for " << fname << std::endl;
		return;
	}

	//avcodec_open is not thread safe
//		lock();
	if(avcodec_open(pCodecCtx, pCodec)<0) {
		std::cout << "avcodec: cannot open " << fname << std::endl;
		return;
	}
//		unlock();

	pFrame=avcodec_alloc_frame();
	channels = pCodecCtx->channels;

	if(channels > 2){
		std::cout << "ffmpeg: No support for more than 2 channels!" << std::endl;
		return;
	}
}

int ffmpeg::get_length() {
}

int ffmpeg::get_pos() {
}

bool ffmpeg::seek(unsigned long long seek_pos) {
}

bool ffmpeg::process(float *buffer_l, float *buffer_r, int samplecount) {
}



  void init(char *fname = "/shared/mp3/speed.mp3") {

		//filelength = (long int) ((double)pFormatCtx->duration * 2 / AV_TIME_BASE * SRATE);
  }

	bool readInput(){
		char *dst;
		unsigned char *src;
		int ret = 0;
		int readsize = 0;
		int inputsize = 0;
			int tries = 0;
		//DEBUG
		bufferSize = 0;
		bufferOffset = 0;
		memset(buffer, 0, AVCODEC_MAX_AUDIO_FRAME_SIZE);
		while (av_read_packet(pFormatCtx, &packet)>0) {
			if (packet.stream_index==audioStream){
				dst = (char *)buffer;
				src = packet.data;
				inputsize = 0;
				readsize = 0;
				//qDebug("ffmpeg: before avcodec_decode_audio packet.size(%d)", packet.size);
				tries = 0;
				do {
					ret = avcodec_decode_audio(pCodecCtx, (int16_t *)dst, &readsize, src, packet.size - inputsize);
					if (readsize == 0)
					{
						tries++;
						//qDebug("ffmpeg: skip frame, decoded readsize = 0");
						break;
					}
					if (ret <= 0)
					{
						tries++;
						//qDebug("ffmpeg: skip frame, decoded ret = 0");
						if (tries > 3) break;
						continue;
					}
					//qDebug("0:%d 1:%d 2:%d -- 3:%d 4:%d 5:%d 6:%d", dst[1], dst[45], dst[100], dst[readsize-1], dst[readsize], dst[readsize/2-1], dst[readsize/2]);
					dst += readsize;
					bufferSize += readsize;
					src += ret;
					inputsize += ret;
					//qDebug("ffmpeg: loop buffersize(%d), readsize(%d) ret(%d) psize(%d)", bufferSize, readsize, ret, packet.size);
				} while (inputsize < packet.size);
				//qDebug("ffmpeg: after avcodec_decode_audio outsize(%d) - ret(%d)", bufferSize, ret);
				if (bufferSize != 0)
					return true;

			}
			//debug
			av_free_packet(&packet);
		}
		return false;
	}
