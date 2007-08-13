/*
** pool.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Mon Aug  6 22:26:18 2007 Nahlwe
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

#ifndef   	POOL_HH_
# define   	POOL_HH_

namespace Rt
{

  /*!
  ** \brief Pool based memory manager (1).
  ** This allocator is not thread safe.
  */

  class Chunk
  {
  public:
    typedef uint32_t    address;

  public:
    Chunk(unsigned int a_chunk_size, unsigned int a_chunk_capacity);
    ~Chunk();

    /// \return 0 if there is no more memory available in this chunk.
    template <class DataType>
    DataType                    *alloc();

    template <class DataType>
    void                        dealloc(DataType *);

    void                        debug_free(); /// \internal display the free chunk lifo.
  protected:
    unsigned int                m_chunk_size;
    unsigned int                m_chunk_capacity;
    volatile unsigned int       m_free_chunks;
    void                        *m_heap;
    address                     *m_free;
    Chunk                       *m_next_chunk;
  };
};

#include "pool.cc"

#endif	    /* !POOL_HH_ */


