/*
** iInput.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Fri Jan 26 03:56:19 2007 Nahlwe
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

#ifndef   	IINPUT_HH_
# define   	IINPUT_HH_

#include "thread.hpp"
#include "lfringbuffer.hh"

/** Interface for input class.
 * Can be added to kInputRegistry
 */
template <class InputType>
class iInput : public iFoncteur0<void>
{
public:
  iInput(Semaphore &a_sem, uint32_t buffer_size);
  virtual LFRingBufferReader<InputType> *get_reader();
protected:
  virtual void                  thread_fun() = 0; /** Input loop thread function */
  void                          operator()();

  LFRingBuffer<InputType>       m_buffer;
  LFRingBufferWriter<InputType> *m_writer;
  Semaphore                     &m_sem;
  Thread                        m_thread;
};

#include "iInput.cpp"

#endif	    /* !IINPUT_HH_ */

