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

noinst_HEADERS =

include_HEADERS = timer.hh iSynth.hh part.hh seq.hh Sequence.hh event_bus.hh transport.hh event.hh

#######################
# Build an executable #
#######################

#INCLUDES = -I $(top_builddir)/src

lib_LTLIBRARIES = libseq.la
libseq_la_SOURCES = timer.cc transport.cc part.cc seq.cc event.cc
libseq_la_CXXFLAGS = -g3 @SIGC_CFLAGS@
libseq_la_LIBADD = -lrt @SIGC_LIBS@
libseq_la_LDFLAGS =


# Don't forget that the order of the libraries _does_ matter


##########
# Checks #
##########

TESTS = test_position
check_PROGRAMS = test_position
test_position_SOURCES = test_position.cc transport.cc \
	timer.cc
test_position_CXXFLAGS = @SIGC_CFLAGS@
test_position_LDADD = @SIGC_LIBS@


####################
# Additional Rules #
####################

re : clean all

c : clean

a : all

