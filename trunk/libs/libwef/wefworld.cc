/*
** wefworld.cc
** Login : <elthariel@elthariel-desktop>
** Started on  Sun Jun  3 23:53:12 2007 Nahlwe
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
#include "wefworld.hh"
#include <cstdlib>
#include <sys/types.h>
#include <dirent.h>


using namespace std;

WefWorld::WefWorld()
{
  init();
}

WefWorld::~WefWorld()
{
  WefList::iterator i;

  for (i = m_wefs.begin(); i != m_wefs.end(); i++)
    {
      delete *i;
    }
}

void            WefWorld::load_wef(const char *a_path)
{
  Wef *new_wef = new Wef(a_path);

  m_wefs.push_back(new_wef);
}

void            WefWorld::search_wef(std::string &a_dir)
{
  DIR           *dir;
  struct dirent *file;

  dir = opendir(a_dir.c_str());
  if (!dir)
    {
      cout << "Directory couldn't be open :" << a_dir << endl;
      return;
    }
  while(file = readdir(dir))
    {
      //FIXME omit non wef files, use scandir
      load_wef(file->d_name);
    }
}

std::string     WefWorld::get_next_path(std::string &a_env)
{
  string res;
  string::size_type pos;

  if ((pos = a_env.find(";")) == string::npos)
    return a_env;
  res = a_env.substr(0, pos);
  a_env = a_env.substr(pos + 1);
  return res;
}

void            WefWorld::init()
{
  char          *cpath = getenv("WEF_PATH");
  string        path;
  if (cpath)
    path = cpath;
  else
    path = "/usr/share/wef";

  string current;

  while ((current = get_next_path(path)) != "")
    search_wef(current);
}
