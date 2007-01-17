##
## Makefile
## Login : <elthariel@elthariel-desktop>
## Started on  Tue Jan 16 03:48:52 2007 Nahlwe
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

OBJS						= main.o WaView.o
OUT							= test_waview
CXXFLAGS				= -g -Wall $(shell pkg-config --cflags gtkmm-2.4)
LDFLAGS					= $(shell pkg-config --libs gtkmm-2.4) -lsndfile

all : $(OUT)

$(OUT): $(OBJS)
	g++ -o $(OUT) $(CXXFLAGS) $(LDFLAGS) $(OBJS)

c :
	rm -f $(OBJS) $(OUT)

t : all
	./$(OUT)

ec :
	rm -f *~ \#*\#

.cc.o:
	g++ -c $(CXXFLAGS) $<
