/*
** iInput.cpp
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

#ifndef IINPUT_CPP_
# define IINPUT_CPP_

#include "iInput.hh"

template <class InputType>
iInput<InputType>::iInput(Semaphore &a_sem, uint32_t buffer_size)
  : m_sem(a_sem),
    m_thread(*this),
    m_buffer(buffer_size)
{
  m_writer = m_buffer.get_writer();
}

template <class InputType>
LFRingBufferReader<InputType>   *iInput<InputType>::get_reader()
{
  return m_buffer.get_reader();
}

template <class InputType>
void                            iInput<InputType>::operator()()
{
  thread_fun();
}

#endif
