/*
** lfringbuffer.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Thu Jan 25 05:34:27 2007 Nahlwe
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

#ifndef   	LFRINGBUFFER_HH_
# define   	LFRINGBUFFER_HH_

template <class BlockType>
class LFRingBuffer;

template <class BlockType>
class LFRingBufferReader
{
public:
  bool                  read(BlockType *out);
  bool                  ready();

private:
  LFRingBufferReader(LFRingBuffer<BlockType> &);
  LFRingBufferReader();
  ~LFRingBufferReader();

  LFRingBuffer<BlockType>       &ring;

  friend class LFRingBuffer<BlockType>;
};






template <class BlockType>
class LFRingBufferWriter
{
public:
  bool                  write(BlockType *out);
  bool                  ready();

private:
  LFRingBufferWriter(LFRingBuffer<BlockType> &);
  LFRingBufferWriter();
  ~LFRingBufferWriter();

  LFRingBuffer<BlockType>       &ring;

  friend class LFRingBuffer<BlockType>;
};







template <class BlockType>
class LFRingBuffer
{
public:
  LFRingBuffer(uint32_t item_count);

  LFRingBufferWriter<BlockType>         *get_writer();
  LFRingBufferReader<BlockType>         *get_reader();

protected:
  LFRingBuffer();

  void                  reader_deleted();
  void                  writer_deleted();

  bool                  write(BlockType *out);
  bool                  ready_to_write();
  bool                  read(BlockType *out);
  bool                  ready_to_read();

  BlockType             *m_buffer;
  volatile uint32_t     m_ro;
  volatile uint32_t     m_wo;
  volatile uint32_t     m_capacity;
  volatile uint32_t     m_occupation;
  volatile bool         m_reader;
  volatile bool         m_writer;

  friend class LFRingBufferWriter<BlockType>;
  friend class LFRingBufferReader<BlockType>;
};

#endif	    /* !LFRINGBUFFER_HH_ */
