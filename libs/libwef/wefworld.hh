/*
** wefworld.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Sun Jun  3 23:52:25 2007 Nahlwe
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

#ifndef   	WEFWORLD_HH_
# define   	WEFWORLD_HH_

#include "wef.hh"
#include <list>
#include <string>

typedef std::list<Wef *> WefList;

class WefWorld
{
public:
  WefWorld();
  ~WefWorld();

protected:
  void          load_wef(const char *a_path);
  void          search_wef(std::string &a_dir);
  void          init();
  std::string   get_next_path(std::string &a_env);

  WefList       m_wefs;
};

#endif	    /* !WEFWORLD_HH_ */
