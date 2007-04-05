/*
** iOutput.cc
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

#ifndef IOUTPUT_CPP_
# define IOUTPUT_CPP_

#include <iostream>
#include "iOutput.hh"

using namespace std;

template <class OutputType>
iOutput<OutputType>::iOutput(uint32_t a_buf_size)
 : m_buffer(a_buf_size)
{
}

template <class OutputType>
LFRingBufferWriter<OutputType> *iOutput<OutputType>::get_writer()
{
  return m_buffer.get_writer();
}

template <class OutputType>
Thread                &iOutput<OutputType>::run()
{
  m_thread = new Thread(*this);
  return m_thread;
}

template <class OutputType>
Semaphore             &iOutput<OutputType>::get_sem()
{
  return m_sem;
}

template <class OutputType>
void          iOutput<OutputType>::operator()()
{
  thread_fun();
}

#endif
