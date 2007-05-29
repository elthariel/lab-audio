/*
** test_lv2.cc
** Login : <elthariel@elthariel-desktop>
** Started on  Tue May 29 20:35:12 2007 Nahlwe
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
#include <assert.h>
#include "lv2Manager.hh"

using namespace std;

int main(int argc, char **argv)
{
  SLV2World world = slv2_world_new();
  slv2_world_load_all(world);

  if (argc != 2) {
    fprintf(stderr, "Usage: %s PLUGIN_URI\n", argv[0]);
    return -1;
  }

  SLV2Plugins plugins = slv2_world_get_all_plugins(world);

  SLV2Plugin p = slv2_plugins_get_by_uri(plugins, argv[1]);
  //  Lv2Adapter lv2(p, 48000);

  unsigned int m_port_count = slv2_plugin_get_num_ports(p);

  cout << "This plugin has " << m_port_count << " ports." << endl;
}
