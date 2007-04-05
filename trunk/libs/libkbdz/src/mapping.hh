/*
** mapping.hh
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

#ifndef   	MAPPING_HH_
# define   	MAPPING_HH_

#include <list>
#include <sigc++/sigc++.h>
#include "kevent.hh"
#include "iInput.hh"
#include "iOutput.hh"

template <class OutType>
class iMapping : public sigc::trackable
{
public:
  void                  set_out(LFRingBufferWriter<OutType> *a_out);
  void                  add_out(LFRingBufferWriter<OutType> *a_out);
  void                  rem_out(LFRingBufferWriter<OutType> *a_out);
  virtual bool          accept(kEvent &) = 0;
private:
  typedef LFRingBufferWriter<OutType> Out;
  std::list<Out *>      m_outs;
};

#endif	    /* !MAPPING_HH_ */
