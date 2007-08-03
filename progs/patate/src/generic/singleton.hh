/*
** singleton.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Thu Aug  2 21:08:41 2007 Nahlwe
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

#ifndef   	SINGLETON_HH_
# define   	SINGLETON_HH_

template <class T>
class Singleton
{
public:
  static T              &get()
  {
    if (!m_instance)
      m_instance = new T();
    return *m_instance;
  }

protected:
  static T      *m_instance;
};

template <class T>
class SingletonInitialized
{
public:
  static T              &get()
  {
    return *m_instance;
  }

  static void           init(T &a_instance)
  {
    if (!m_instance)
      m_instance = a_instance;
  }

protected:
  static T      *m_instance;
};

#endif	    /* !SINGLETON_HH_ */
