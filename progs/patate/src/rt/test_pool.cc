/*
** test_pool.cc
** Login : <elthariel@elthariel-desktop>
** Started on  Wed Aug  8 20:08:56 2007 Nahlwe
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
#include "pool.hh"

using namespace std;
using namespace Rt;

int main(int ac, char **av)
{
  typedef char          block;
  block                 *b[8];;
  unsigned int          size = 8;
  Chunk                 c(sizeof(block), size);

  c.debug_free();
  b[0] = c.alloc<block>();
  c.debug_free();
  b[1] = c.alloc<block>();
  b[2] = c.alloc<block>();
  c.debug_free();
  c.dealloc(b[1]);
  c.debug_free();
  c.dealloc(b[0]);
  c.dealloc(b[2]);
  c.debug_free();

}



