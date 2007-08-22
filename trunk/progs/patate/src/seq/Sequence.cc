/*
** Sequence.cc
** Login : <lta@elthariel-main>
** Started on  Wed Jun 27 06:26:19 2007 Elthariel
** $Id$
**
** Copyright (C) 2007 Elthariel
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

namespace Seq
{

template <class T>
Sequence<T>::Sequence(short a_res,unsigned short a_seq_len, EventBus<T> *a_bus)
  : m_out(a_bus), m_seq_len(a_seq_len), m_res(a_res)
{
  if (m_res == 0)
    m_res = 1;
}

template <class T>
void                                  Sequence<T>::connect(EventBus<T> *a_bus)
{
  m_out = a_bus;
}

template <class T>
void                                  Sequence<T>::play(tick a_pos, tick a_len)
{
  const_iterator                      iter;

  if (m_out)
    {
      iter = m_seq.lower_bound(a_pos);
      while(iter->first < a_pos + a_len)
        {
          m_out->send(*(iter->second));
          iter++;
        }
    }
}

template <class T>
void                                  Sequence<T>::add(tick a_pos, T &a_event)
{
  value_type                          new_pair(a_pos, &a_event);

  /*  new_pair.first = a_pos;
      new_pair.second = &a_event;*/
  m_seq.insert(new_pair);
}

template <class T>
void                                  Sequence<T>::remove(tick a_pos)
{
  m_seq.erase(a_pos);
}

template <class T>
void                                  Sequence<T>::remove_range(tick low_bound, tick high_bound)
{
  // FIXME
  std::cout << "Sequence::remove_range : unimplemented" << std::endl;
}

template <class T>
void                                  Sequence<T>::clear()
{
  //FIXME take care of event memory (delete if necessary)
  m_seq.clear();
}

template <class T>
short                                 Sequence<T>::get_res()
{
  return m_res;
}

template <class T>
void                                  Sequence<T>::set_res(short a_new_res)
{
  m_res = a_new_res;
}

template <class T>
unsigned short                        Sequence<T>::get_len()
{
  return m_seq_len;
}

template <class T>
void                                  Sequence<T>::set_len(unsigned short a_new_len)
{
  m_seq_len = a_new_len;
}

  template <class T>
  void                                  Sequence<T>::move(iterator iter, tick new_pos)
  {
    T                                   *ev = iter->second;
    value_type                          val(new_pos, ev);

    m_seq.erase(iter);
    m_seq.insert(val);
  }

  template <class T>
  void                                  Sequence<T>::move(tick old_pos, T &event, tick new_pos)
  {
    iterator i = m_seq.find(old_pos);
    while((i->second != &event) & (i != m_seq.end()))
      i++;
    move(i, new_pos);
  }

};

