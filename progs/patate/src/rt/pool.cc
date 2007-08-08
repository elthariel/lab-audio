/*
** pool.cc
** Login : <elthariel@elthariel-desktop>
** Started on  Tue Aug  7 22:56:28 2007 Nahlwe
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
#include <cstdlib>
#include "pool.hh"


namespace Rt
{
  Chunk::Chunk(unsigned int a_chunk_size, unsigned int a_chunk_capacity)
    : m_chunk_capacity(a_chunk_capacity),
      m_free_chunks(a_chunk_capacity)
  {
    unsigned int i;

    m_chunk_size = a_chunk_capacity + (a_chunk_capacity % 8);
    m_heap = malloc(m_chunk_size * a_chunk_capacity);
    m_free = (uint32_t *)malloc(a_chunk_capacity * sizeof(address));
    for (i = 0; i < a_chunk_capacity; i++)
      m_free[i] = i;
  }

  Chunk::~Chunk()
  {
    free(m_heap);
    free(m_free);
  }

  template <class DataType>
  DataType            *Chunk::alloc()
  {
    address               p;
    ///  \todo use Compare and swap
    ///  \todo support chunk chaining
    if(m_free_chunks)
      {
        p = m_free[m_free_chunks];
        m_free_chunks--;
        return (m_heap + p);
      }
    else
      return (0);
  }

  template <class DataType>
  void                Chunk::dealloc(DataType *p)
  {
    address a = (address) p;
    if ((p < m_heap) | (p > (m_heap + m_chunk_capacity)))
      return;
    a -= (address) m_heap;
    a /= m_chunk_size;
    m_free[++m_free_chunks] = a;
    return;
}
};


