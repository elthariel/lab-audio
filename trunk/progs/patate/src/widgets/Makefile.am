##
## Makefile.am
## Login : <elthariel@elthariel-desktop>
## Started on  Thu Apr 26 12:11:05 2007 Nahlwe
## $Id$
##
## Copyright (C) 2007 Nahlwe
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
##

## immediate subdirs
## extra files
EXTRA_DIST =

noinst_HEADERS = kbd_view.hh roll_view.hh

include_HEADERS =

###################
# Build a library #
###################
#                 #
############################################################
# librtsa = Real Time data Structure and Algorithm Library #
############################################################

INCLUDES = -I ../src -I../seq

lib_LTLIBRARIES = libwidgets.la
libwidgets_la_SOURCES = kbd_view.cc roll_view.cc
libwidgets_la_CXXFLAGS = @PKG_CFLAGS@
libwidgets_la_LIBADD = @PKG_LIBS@ -L../seq -lseq
libwidgets_la_LDFLAGS =


# Don't forget that the order of the libraries _does_ matter


##########
# Checks #
##########

TESTS = test_gtk
check_PROGRAMS = test_gtk
test_gtk_SOURCES = main.cc kbd_view.cc roll_view.cc
test_gtk_CXXFLAGS = @PKG_CFLAGS@
test_gtk_LDADD = @PKG_LIBS@ -L../seq -lseq


####################
# Additional Rules #
####################

re : clean all

c : clean

a : all

