/*
** sequence.hh
** Login : <elthariel@localhost.localdomain>
** Started on  Sat Dec  2 03:37:15 2006 Elthariel
** $Id$
**
** Copyright (C) 2006 Elthariel
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

# include "outbus.hh"

class                   Sequence
{
private:
  Sequence();

protected:
  OutBus                &m_outbus;
  unsigned char         m_res;
  unsigned int          m_tick;
  unsigned char         m_len;
public:
  Sequence(OutBus &a_outbus);

  virtual void          clear() = 0;
  virtual void          play(unsigned int a_tick_offset) = 0;
  virtual void          stop() = 0;
  virtual void          set_res(unsigned char a_res) = 0;
  virtual void          set_len(unsigned char a_len) = 0;

};

#endif	    /* !SEQUENCE_HH_ */
