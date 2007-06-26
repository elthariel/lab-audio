/*
** Sequence.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Tue Jun 26 23:29:42 2007 Nahlwe
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

#ifndef   	SEQUENCE_HH_
# define   	SEQUENCE_HH_

#include <multimap>

/*!
** \brief Represents a sequence on (musical) event.
** Implemented using multimap (red-black tree) assuring logarithmic worst
** time complexity (if no duplicate keys).
**
** Should be used with a real-time safe allocator.
*/
template <class T>
class Sequence
{
  typedef T                             value_type;
  typedef T *                           pointer;
  typedef const T *                     const_pointer;
  typedef T &                           reference;
  typedef const T &                     const_reference;
  typedef uint32_t                      tick_type;
  typedef std::multimap<tick, T*>       _sequence;
  typedef _sequence::iterator           iterator;
  typedef const _sequence::iterator     const_iterator;

public:
protected:
};

#endif	    /* !SEQUENCE_HH_ */
