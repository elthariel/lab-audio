/*
** lo_avahi.h
** Login : <elthariel@localhost.localdomain>
** Started on  Fri Jan 12 17:06:15 2007 Elthariel
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

#ifndef   	LO_AVAHI_H_
# define   	LO_AVAHI_H_

int             lo_avahi_init(lo_server s);
void            lo_avahi_callback(AvahiClient *ac,
                                  AvahiClientState state, void *usserdata);
int             lo_avahi_create_service(lo_server s);
void            lo_avahi_group_callback(AvahiEntryGroup *group,
                                        AvahiEntryGroupState state,
                                        void *userdata);

//FIXME remove
void            my_err_h(int num, const char *msg, const char *path);

#endif 	    /* !LO_AVAHI_H_ */
