/*
** aseq_output.cpp
** Login : <elthariel@elthariel-desktop>
** Started on  Tue Apr  3 00:54:51 2007 Nahlwe
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

#include <iostream>
#include "aseq_output.hh"

ASeqOutput::ASeqOutput()
  : iOutput<kEvent>::iOutput(100),
    m_aseq(0),
    m_active(true)
{
  if (open_aseq())
    if (open_port())
      cerr << "Alsa seq initialized" << endl;
    else
      cerr << "Unable to open port" << endl;
  else
    cerr << "Unable to initalize alsa seq" << endl;
}

void                    ASeqOutput::thread_fun()
{
  kEvent                ev;

  while (m_active)
    {
      --m_sem;
      if (m_reader->ready())
        {
          m_reader->read(&ev);
          send_event(ev);
        }
    }
}

bool                    ASeqOutput::open_aseq()
{
  int err;

  err = snd_seq_open(&m_aseq, "default", SND_SEQ_OPEN_OUTPUT, 0);
  if (err < 0)
    return false;
  snd_seq_set_client_name(m_aseq, "kbdz_aseq");
  return true;
}

bool                    ASeqOutput::open_port()
{
  m_port = snd_seq_create_simple_port(m_aseq,
                                      "kbdz_out",
                                      SND_SEQ_PORT_CAP_READ |
                                      SND_SEQ_PORT_CAP_SUBS_READ,
                                      SND_SEQ_PORT_TYPE_MIDI_GENERIC);
  if (m_port < 0)
    return false;
  else
    return true;
}

void                    ASeqOutput::send_event(kEvent &a_ev)
{
  snd_seq_event_t       ev;

  cerr << "I should have send an envent using aseq" << endl;
}
