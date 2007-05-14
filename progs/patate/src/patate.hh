/*
** patate.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Wed Apr  4 12:28:10 2007 Nahlwe
** $Id$
**
** Copyright (C) 2007 Nahlwe
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#ifndef   	PATATE_HH_
# define   	PATATE_HH_

#include <exception>
#include <jack/jack.h>
#include <jack/midiport.h>
#include "lfringbuffer.hh"
#include "event.hh"
#include "sampler.hh"
#include "seq.hh"

#define PATATE_SEQ_PPQ         96
#define PATATE_SAMPLER_COUNT   16

class Patate
{
public:
  Patate(LFRingBufferWriter<Event> *a_writer,
         LFRingBufferReader<Event> *a_reader);
  ~Patate();

  int                   process(jack_nframes_t nframes);
  Sampler               &get_sampler();
  Seq::Seq              &get_drumseq();

protected:
  void                  init_jack();
  void                  close_jack();
  void                  process_midi(jack_nframes_t nframes);
  void                  process_event();
  void                  process_audio(jack_nframes_t nframes,
                                      jack_nframes_t sample_rate);
  void                  _process_event(Event &a_ev);
  void                  process_seq(jack_nframes_t nframes,
                                    jack_nframes_t sample_rate);
  void                  set_bpm(unsigned int a_new_bpm);

  LFRingBufferWriter<Event> *m_writer; // to the gui
  LFRingBufferReader<Event> *m_reader; // from the gui
  Sampler               m_sampler;
  Seq::Seq              m_seq;
  jack_client_t         *m_jack_client;
  jack_port_t           *m_midi_port;
  jack_port_t           *m_audio_port_l;
  jack_port_t           *m_audio_port_r;
  jack_nframes_t        m_buffer_size;
  unsigned int          m_bpm;
  //  float                 m_remaining_samples;
};

class jack_error : public std::exception
{
public:
  jack_error(const char *a_err);
  virtual const char *what() const throw();
protected:
  const char    *m_err;
};

#endif	    /* !PATATE_HH_ */
