/*
** lfringbuffer.cc
** Login : <elthariel@elthariel-desktop>
** Started on  Thu Jan 25 05:43:13 2007 Nahlwe
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
#include "lfringbuffer.hh"

template <class BlockType>
LFRingbuffer::LFRingbuffer(uint32_t item_count)
  : m_buffer(0), m_ro(0), m_wo(0), m_capacity(item_count),
    m_size(), m_reader(false), m_writer(false)
{
  m_buffer = new BlockType[item_count];
}

template <class BlockType>
LFRingBufferWriter<BlockType>   *LFRingbuffer::get_writer()
{
  if (m_writer)
    return (0);
  else
    return (new LFRingBufferWriter<BlockType>(*this));
}

template <class BlockType>
LFRingBufferReader<BlockType>   *LFRingbuffer::get_reader()
{
  if (m_reader)
    return (0);
  else
    return (new LFRingBufferReader<BlockType>(*this));
}

template <class BlockType>
void            LFRingbuffer::reader_deleted()
{
  m_reader = false;
}

template <class BlockType>
void            LFRingbuffer::writer_deleted()
{
  m_writer = false;
}

template <class BlockType>
bool            LFRingbuffer::write(BlockType *out)
{
  bool          ret = ready_to_write();
  if (ret)
    {
      m_buffer[m_wo] = *out;
      m_wo++;
      m_wo %= m_capacity;
      m_size--;
    }
  return (ret);
}

template <class BlockType>
bool            LFRingbuffer::read(BlockType *out)
{
  bool          ret = ready_to_read();
  if (ret)
    {
      *out = m_buffer[m_ro];
      m_ro++;
      m_ro %= m_capacity;
      m_size++;
    }
  return (ret);
}

template <class BlockType>
bool            LFRingbuffer::ready_to_write()
{
  return (m_size < m_capacity);
}

template <class BlockType>
bool            LFRingbuffer::ready_to_read()
{
  return (!(m_size > 0));
}

// Reader

template <class BlockType>
LFRingBufferReader::LFRingBufferReader(LFRingBuffer<BlockType> &ringbuf)
  : ring(ringbuf)
{
}

template <class BlockType>
LFRingBufferReader::~LFRingBufferReader()
{
  ring.reader_deleted();
}

template <class BlockType>
bool            LFRingBufferReader::read(BlockType *out)
{
  return (ring.read(out));
}

template <class BlockType>
bool            LFRingBufferReader::ready()
{
  return (ring.ready_to_read());
}

template <class BlockType>
LFRingBufferWriter::LFRingBufferWriter(LFRingBuffer<BlockType> &ringbuf)
  : ring(ringbuf)
{
}

template <class BlockType>
LFRingBufferWriter::~LFRingBufferWriter()
{
  ring.writer_deleted();
}

template <class BlockType>
bool            LFRingBufferWriter::read(BlockType *out)
{
  return (ring.write(out));
}

template <class BlockType>
bool            LFRingBufferWriter::ready()
{
  return (ring.ready_to_write());
}
