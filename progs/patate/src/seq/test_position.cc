/*
** test_position.cc
** Login : <elthariel@elthariel-desktop>
** Started on  Sun Aug  5 16:56:49 2007 Nahlwe
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
#include "transport.hh"

using namespace std;
using namespace Seq;

static void print_pos(Transport::Position pos)
{
  cout << "Position :\t" << pos.bars << " \t" << pos.beats << " \t" << pos.ticks << endl;
}

int main(int ac, char **av)
{
  TimerSingleton::init(*new Timer());
  cout << "ppq is : " << TimerSingleton::get().ppq() << endl;

  Transport::Position a(1, 1, 95), b(3, 3, 50);
  Transport::Position c(15000);
  Transport::Position tmp;
  uint64_t t;

  cout << "printing a, b, and c" << endl;
  print_pos(a);
  print_pos(b);
  print_pos(c);
  cout << "printing a + b" << endl;
  a += b;
  print_pos(a);

  t = c;
  cout << "c in ticks : " << t << endl;
}


