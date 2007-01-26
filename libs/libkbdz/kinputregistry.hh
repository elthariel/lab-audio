/*
** kinputregistry.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Fri Jan 26 06:52:51 2007 Nahlwe
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

#ifndef   	KINPUTREGISTRY_HH_
# define   	KINPUTREGISTRY_HH_

#include <vector>
#include "iInput.hh"

class kInputRegistry
{
public:
  kInputRegistry();
  ~kInputRegistry();

  void                                  register_input(iInput &);
  void                                  unregister_input(iInput &);
private:
  mutex                                 m_mutex; // Mutex to protect access to m_inputs.
  std::list<iInput &>                   m_inputs;
  std::list<LFRingBufferReader<kEvent> &> m_readers;

  friend class kInputRegistryIterator;
};

/** InputRegistry iterator, provides access to the input modules.
 * Enforce locking policy. the registry is locked when registering or
 * unregistering Inpute modules.
 */
class kInputRegistryIterator
{
};

#endif	    /* !KINPUTREGISTRY_HH_ */
