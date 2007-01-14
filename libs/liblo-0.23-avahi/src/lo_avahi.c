/*
** lo_avahi.c
** Login : <elthariel@localhost.localdomain>
** Started on  Fri Jan 12 18:32:11 2007 Elthariel
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


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <float.h>
#include <sys/types.h>

#include <netdb.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <sys/un.h>
#include <arpa/inet.h>

#include "lo_types_internal.h"
#include "lo/lo.h"
#include "lo/lo_throw.h"
#ifndef WIN_32
#include <lo/lo_avahi.h>
#endif

int             lo_avahi_init(lo_server s)
{
  int avahi_error;

  s->av_client = 0;
  s->av_simple_poll = 0;
  s->av_group = 0;

  if (!(s->av_simple_poll = avahi_simple_poll_new()))
    lo_throw(s, -42, "Failed to create avahi simple_poll object\n", NULL);
  s->av_client = avahi_client_new(avahi_simple_poll_get(s->av_simple_poll),
                                  0,//AVAHI_CLIENT_NO_FAIL,
                                  &lo_avahi_callback, (void *)s,
                                  &avahi_error);
  if (!s->av_client)
    fprintf(stderr, "Unable to create client %s \n",
            avahi_strerror(avahi_error));
    //    lo_throw(s, -42, "Failed to create avahi client object\n", NULL);
  return (0);
}

void            lo_avahi_callback(AvahiClient *ac,
                                  AvahiClientState state, void *userdata)
{
  lo_server     s;

  s = (lo_server)userdata;

  if (ac)
    {
    	s->av_client = ac;
      switch (state)
        {
        case AVAHI_CLIENT_S_RUNNING:
          fprintf(stderr, "AVAHI_CLIENT_S_RUNNING\n");
          if (!s->av_group){
            if (lo_avahi_create_service(s))
              {
                fprintf(stderr, "AVAHI_CLIENT_S_RUNNING, unable to create service\n");
                if (s->av_group)
                  avahi_entry_group_reset(s->av_group);
              }
          }
          break;

        case AVAHI_CLIENT_FAILURE:
          //FIXME lo_throw
          fprintf(stderr, "Client failure: %s\n",
                  avahi_strerror(avahi_client_errno(ac)));
          avahi_simple_poll_quit(s->av_simple_poll);
          break;

        case AVAHI_CLIENT_S_COLLISION:
          fprintf(stderr, "AVAHI_CLIENT_S_COLLISION\n");

        case AVAHI_CLIENT_S_REGISTERING:
          fprintf(stderr, "AVAHI_CLIENT_S_REGISTERING \n");
          if (s->av_group)
            avahi_entry_group_reset(s->av_group);
          break;

        case AVAHI_CLIENT_CONNECTING:
          fprintf(stderr, "AVAHI_CLIENT_CONNECTING \n");
          break;
        }
    }
  else
    {
      fprintf(stderr, "Avahi client is == 0 \n");
    }
}

int             lo_avahi_create_service(lo_server s)
{
  int ret;

  if (s->av_client && !s->av_group)
    {
      s->av_group = avahi_entry_group_new(s->av_client,
                                          &lo_avahi_group_callback,
                                          (void *)s);

       if (!s->av_group)
        {
          lo_throw(s, 0,
                   "libo: avahi: Unable to create entry group\n", NULL);
          fprintf(stderr, "Unable to commit group entry : %s\n",
                  avahi_strerror(avahi_client_errno(s->av_client)));

          return (-1);
        }

      ret = avahi_entry_group_add_service(s->av_group,
                                          AVAHI_IF_UNSPEC, //send on all if.
                                          AVAHI_PROTO_UNSPEC, //with all proto
                                          0,
                                          "OSCtest",            //May need fixme.
                                          "_osc._udp",
                                          0, 0, s->port,
                                          "a test txt", NULL);
      if (ret < 0){
        fprintf(stdout, "Failed to add osc service: %s\n", avahi_strerror(ret));
        return (-1);
      }


      if ((ret = avahi_entry_group_commit(s->av_group) < 0)){
        fprintf(stdout, "Unable to commit group entry : %s\n", avahi_strerror(ret)); //FIXME replace by lo_throw
        return (-1);
      }
    }
  else
    {return (-1);}
  return (0);
}

void            lo_avahi_group_callback(AvahiEntryGroup *group,
                                        AvahiEntryGroupState state,
                                        void *userdata)
{
  lo_server     s;

  s = (lo_server)userdata;
  if ((group == s->av_group) || (group == NULL))
    {
      switch (state)
        {
          fprintf(stderr, "received a groupe state\n");
        case AVAHI_ENTRY_GROUP_ESTABLISHED:
          fprintf(stderr,
                  "Service successfully established.\n");
          break;

        case AVAHI_ENTRY_GROUP_COLLISION:
          //FIXME handle group name collision
          fprintf(stderr, "AVAHI_ENTRY_GROUP_COLLISION:\n");
          break;

        case AVAHI_ENTRY_GROUP_FAILURE:
          avahi_simple_poll_quit(s->av_simple_poll);
          fprintf(stderr, "AVAHI_ENTRY_GROUP_FAILURE\n");
          break;

        case AVAHI_ENTRY_GROUP_UNCOMMITED:
          fprintf(stderr, "AVAHI_ENTRY_GROUP_UNCOMMITED:\n");
        case AVAHI_ENTRY_GROUP_REGISTERING:
          fprintf(stderr, "AVAHI_ENTRY_GROUP_REGISTERING:\n");
          ;
        }
    }
  else
    fprintf(stderr, "Group was not created");
}

void            my_err_h(int num, const char *msg, const char *path)
{
  fprintf(stderr, "liblo: Error num %d,\n\terror msg: %s,\n\t path: %s\n",
          num, msg, path);
}
