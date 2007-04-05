/*
** mapping.cpp
** Login : <elthariel@elthariel-desktop>
** Started on  Tue Apr  3 19:37:23 2007 Nahlwe
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
#include "mapping.hh"

using namespace std;

template <class OutType>
void    iMapping<OutType>::set_out(LFRingBufferWriter<OutType> *a_out)
{
  m_outs.clear();
  m_outs.push_back(a_out);
}

template <class OutType>
void    iMapping<OutType>::add_out(LFRingBufferWriter<OutType> *a_out)
{
  m_outs.push_back(a_out);
}

template <class OutType>
void    iMapping<OutType>::rem_out(LFRingBufferWriter<OutType> *a_out)
{
  m_outs.remove(a_out);
}
