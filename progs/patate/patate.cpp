/*
** patate.cpp
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

static int      jack_process_proxy(jack_nframes_t nframes, void *arg)
{
  Patate        *instance = (Patate *)arg;

  return instance->process(nframes);
}

Patate::Patate()
{
  init_jack();
}

Patate::~Patate()
{
  close_jack();
}

void                  Patate::init_jack()
{

  // Opening jack connection
  m_jack_client = jack_client_new("Patate");
  if (m_jack_client == 0)
    throw *(new jack_error("Unable to connect to jack (servernot running ?)"));

  // Register process callback
  jack_set_process_callback(m_jack_client, &jack_process_proxy,
                            (void *)this);

  //Registering midi port.
  m_midi_port = jack_port_register(m_jack_client, "midi_in",
                                   JACK_DEFAULT_MIDI_TYPE,
                                   JackPortIsInput, //| JackPortIsTerminal,
                                   0);
  if (m_midi_port == 0)
    throw *(new jack_error("Unable to create Midi_in port"));
  m_buffer_size = jack_get_buffer_size(m_jack_client);

  //Activating client.
  if (jack_activate(m_jack_client))
    throw *(new jack_error("Unable to activate jack client"));
}

void                  Patate::close_jack()
{
}

int                   Patate::process(jack_nframes_t nframes)
{
  //Midi process
  //Seq process
  //Audio process
}

/*
 * Exception
 */
jack_error::jack_error(const char *a_err)
  : m_err(a_err)
{
}

const char *jack_error::what() const
{
  return m_err;
}
