/*
 *  Copyright (C) 2004 Steve Harris
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  $Id: server_thread.c,v 1.8 2006/01/26 15:00:28 nhumfrey Exp $
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>

#ifdef WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <netdb.h>
#include <sys/socket.h>
#endif

#include "lo_types_internal.h"
#include "lo/lo.h"
#include "lo/lo_throw.h"

static void thread_func(void *data);

lo_server_thread lo_server_thread_new(const char *port, lo_err_handler err_h)
{
    lo_server_thread st = malloc(sizeof(struct _lo_server_thread));
    st->s = lo_server_new(port, err_h);
    st->active = 0;
    st->done = 0;

    if (!st->s) {
	free(st);

	return NULL;
    }

    return st;
}

void lo_server_thread_free(lo_server_thread st)
{
    if (st) {
	if (st->active) {
	    lo_server_thread_stop(st);
	}
	lo_server_free(st->s);
    }
    free(st);
}

lo_method lo_server_thread_add_method(lo_server_thread st, const char *path,
			       const char *typespec, lo_method_handler h,
			       void *user_data)
{
    return lo_server_add_method(st->s, path, typespec, h, user_data);
}

void lo_server_thread_del_method(lo_server_thread st, const char *path,
			       const char *typespec)
{
    lo_server_del_method(st->s, path, typespec);
}

void lo_server_thread_start(lo_server_thread st)
{
    int result;

    if (!st->active) {
	st->active = 1;
	st->done = 0;

	// Create the server thread
	result = pthread_create(&(st->thread), NULL, (void *)&thread_func, st);
	if (result) {
	    fprintf(stderr, "Failed to create thread: pthread_create() returned %s\n", strerror(result));
	}

    }
}

void lo_server_thread_stop(lo_server_thread st)
{
    int result;

    if (st->active) {
	// Signal thread to stop
	st->active = 0;

	// pthread_join waits for thread to terminate
	// and then releases the thread's resources
	result = pthread_join( st->thread, NULL );
	if (result) {
	    fprintf(stderr, "Failed to stop thread: pthread_join() returned %s\n", strerror(result));
	}
    }
}

int lo_server_thread_get_port(lo_server_thread st)
{
    return lo_server_get_port(st->s);
}

char *lo_server_thread_get_url(lo_server_thread st)
{
    return lo_server_get_url(st->s);
}

lo_server lo_server_thread_get_server(lo_server_thread st)
{
    return st->s;
}

int lo_server_thread_events_pending(lo_server_thread st)
{
    return lo_server_events_pending(st->s);
}

static void thread_func(void *data)
{
  lo_server_thread st = (lo_server_thread)data;
  int ret;

  while (st->active) {
    lo_server_recv_noblock(st->s, 10);

    // Run a loop of avahi client main loop.
    // FIXME restart or exit avahi client
    if ((ret = avahi_simple_poll_iterate(st->s->av_simple_poll, 0)) != 0)
      {
        lo_throw(st->s, ret, "Avahi client loop exited", NULL);
      }
  }
  st->done = 1;

  pthread_exit(NULL);
}

void lo_server_thread_pp(lo_server_thread st)
{
    lo_server_pp(st->s);
}

/* vi:set ts=8 sts=4 sw=4: */
