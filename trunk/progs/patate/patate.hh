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

class Patate
{
public:
  Patate();
  ~Patate();

  int                   process(jack_nframes_t nframes);

protected:
  void                  init_jack();
  void                  close_jack();

  jack_client_t         *m_jack_client;
  jack_port_t           *m_midi_port;
  jack_port_t           *m_audioL_port;
  jack_port_t           *m_audioR_port;
  jack_nframes_t        m_buffer_size;
};

class jack_error : public std::exception
{
public:
  jack_error(const char *a_err);
  virtual const char *what() const;
protected:
  const char    *m_err;
}

#endif	    /* !PATATE_HH_ */
