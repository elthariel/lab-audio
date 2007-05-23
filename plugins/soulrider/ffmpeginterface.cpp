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
#include "sndbuffer.h"

/** TODO
 *	lock avopen/avclose
 * 	make ffmpeg init a simgleton class
 */
static bool ffmpeginit = false;

void ffmpeg::ffmpeg_init()
{
  if (!ffmpeginit) {
    av_register_all();
    ffmpeginit = true;
  }
}
/** Ctor
 *
 */
ffmpeg::ffmpeg(unsigned int samplerate) {
  m_packet.data = NULL;
  m_frame = NULL;
  m_codecctx = NULL;
  m_formatctx = NULL;
  m_loaded = false;
  m_samplerate = samplerate;
  m_soundtouch.setChannels(2);
  m_soundtouch.setRate(1.);
  m_soundtouch.setTempo(1.);
  m_soundtouch.setSampleRate(samplerate);
  m_rate = 1.;
}

/** load one file
 *  make all the initialisation
 */
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
  param.sample_rate = m_samplerate;

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
  //dump_format(m_formatctx, 0, str.c_str(), false);

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
  m_samplerate = m_codecctx->sample_rate;
  //in short int
  m_filelength = (unsigned long) ((double)m_formatctx->duration * 2 / AV_TIME_BASE * m_samplerate);
  m_pos = 0;
  if(m_channels > 2){
    std::cerr << "ffmpeg: No support for more than 2 channels!" << std::endl;
    return false;
  }
  m_loaded = true;
  return true;
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
  m_loaded = false;
}

int ffmpeg::get_length() {
  //std::cout << "ffmpeg: getlength=" << m_filelength << std::endl;
  return m_filelength;
}

int ffmpeg::get_pos() {
  //std::cout << "ffmpeg: getpos=" << m_pos << std::endl;
  return m_pos;
}

/** seek into the mp3
 *  two operations: seek then readpacket
 * @return -1 on error, else return the new pos
 */
bool ffmpeg::seek(unsigned long long seek_pos) {
  long fspos;
  //unsigned long ppos;

  //ppos = m_pos;
  AVRational time_base = m_formatctx->streams[m_audiostream]->time_base;
  //fspos = (long)((double)seek_pos / m_samplerate / 2 * AV_TIME_BASE);
  fspos = (long)((double)seek_pos / m_samplerate / 2 * time_base.den);

  if (av_seek_frame(m_formatctx, m_audiostream, fspos, AVSEEK_FLAG_BACKWARD /*AVSEEK_FLAG_ANY*/)) {
    std::cout << "Error seeking" << std::endl;
    return -1;
  }
  m_soundtouch.flush();
  m_bufferoffset = ((float)(fspos - m_formatctx->streams[m_audiostream]->cur_dts) / time_base.den * m_samplerate * 2);
  /*if (m_bufferoffset > m_buffersize) {
    std::cout << "ffmpeg BADOFFFFFFSET buffsize: " << m_buffersize << " offset: " << m_bufferoffset << std::endl;
    m_bufferoffset = 0;
    }*/
  streadpacket(m_bufferoffset);
  m_pos = seek_pos;//(unsigned long)((double)m_formatctx->streams[m_audiostream]->cur_dts / time_base.den * m_samplerate * 2 );
  //std::cout << "seek: seek_pos=" << seek_pos << "value before seeking=" << ppos << std::endl;
  return m_pos;
}



bool ffmpeg::readpacket(){
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

bool ffmpeg::streadpacket(int octetoffset) {
  if (!readpacket())
    return false;
  //TODO check for error octetoffset > m_buffersize)
  //rereadpkt
  copys2f(m_buffer + octetoffset / 2, m_buffer2, (m_buffersize - octetoffset) / 2);
  m_soundtouch.putSamples((soundtouch::SAMPLETYPE*)m_buffer2, m_buffersize / 4);
  return true;
}

int ffmpeg::process(float *buffer_l, float *buffer_r, int samplecount) {
  float *dest_l = buffer_l;
  float *dest_r = buffer_r;
  int index = 0;
  int outsize = 0;
  int tries = 0;
  int needed = samplecount;//*channels

  if (!m_loaded)
    return 0;

  while (needed > 0) {
    index = m_soundtouch.receiveSamples((soundtouch::SAMPLETYPE*)m_outbuffer, needed);
    outsize += index;
    copyf2ff(m_outbuffer, dest_l, dest_r, index * 2);
    m_pos += (float)index * (float)2 / m_rate;//maybe one or two sample could be chopped
    dest_l += index;
    dest_r += index;
    needed -= outsize;
    if (needed > 0) {
      streadpacket();
      ++tries;
      if (tries > 10)
        break;
    }
  }
  return (outsize);
}

