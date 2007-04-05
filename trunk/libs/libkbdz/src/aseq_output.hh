/*
** aseq_output.hh
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

#ifndef   	ASEQ_OUTPUT_HH_
# define   	ASEQ_OUTPUT_HH_

#include "kevent.hh"
#include "iOutput.hh"
#include <alsa/asoundlib.h>

class ASeqOutput : public iOutput<kEvent>
{
public:
  ASeqOutput();

  void                  send_event(kEvent &a_ev);

protected:
  virtual void          thread_fun();
  bool                  open_aseq();
  bool                  open_port();

  snd_seq_t             *m_aseq;
  int                   m_port;
  bool                  m_active;

};

#endif	    /* !ASEQ_OUTPUT_HH_ */
