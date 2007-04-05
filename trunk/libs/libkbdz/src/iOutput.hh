/*
** iOutput.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Mon Apr  2 19:03:27 2007 Nahlwe
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

#ifndef   	IOUTPUT_HH_
# define   	IOUTPUT_HH_

#include <sigc++/sigc++.h>
#include "thread.hpp"
#include "lfringbuffer.hh"

template <class OutputType>
class iOutput : public iFoncteur0<void>,
                public sigc::trackable
{
public:
  iOutput(uint32_t a_buf_size);
  virtual LFRingBufferWriter<OutputType> *get_writer();
  Thread                &run();
  Semaphore             &get_sem();

protected:
  virtual void          thread_fun() = 0;
  virtual void          operator()();

  Semaphore                     m_sem;
  LFRingBuffer<OutputType>      m_buffer;
  LFRingBufferReader<OutputType> *m_reader;
  Thread                        *m_thread;
};

#include "iOutput.cpp"

#endif	    /* !IOUTPUT_HH_ */
