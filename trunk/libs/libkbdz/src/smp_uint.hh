/*
** smp_uint.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Sat Jan 27 08:07:32 2007 Nahlwe
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

#ifndef   	SMP_UINT_HH_
# define   	SMP_UINT_HH_

/** Atomic smp safe int basic operations. Atomicity is guaranteed on a
 * per operation basis, not on a sequence. The is no bound checking,
 * care to unsigned int overflow
 */
class smp_int_t
{
public:
  smp_int_t(uint32_t init = 0) : m_i(init)
  {}

  inline smp_int_t              &operator++()
  {
    __asm__ __volatile__("lock ; incl %0 \n\t" : "=m"(m_i));
    return (*this);
  }
  inline smp_int_t              &operator--()
  {
    __asm__ __volatile__("lock ; decl %0 \n\t" : "=m"(m_i));
    return (*this);
  }
  inline uint32_t               operator+(uint32_t val)
  {
    __asm__ __volatile__("lock ; addl %1, %0 \n\t" : "=m"(m_i) : "r"(val));
    return (m_i);
  }
  inline uint32_t               operator-(uint32_t val)
  {
    __asm__ __volatile__("lock ; subbl %1, %0" :  "=m"(m_i) : "r"(val));
    return (m_i);
  }

  /*  inline uint32_t               uint32_t()
  {
    return (m_i);
    }*/
  inline uint32_t               get_value()
  {
    return m_i;
  }

  inline bool                   operator<(uint32_t val)
  {
    return (m_i < val);
  }

  inline bool                   operator>(uint32_t val)
  {
    return (m_i > val);
  }

  inline bool                   operator<=(uint32_t val)
  {
    return (m_i <= val);
  }

  inline bool                   operator>=(uint32_t val)
  {
    return (m_i >= val);
  }

  inline bool                   operator==(uint32_t val)
  {
    return (m_i == val);
  }

  /*
   * FIXME operator=
   */
private:
  volatile uint32_t     m_i;
};

#endif	    /* !SMP_UINT_HH_ */
