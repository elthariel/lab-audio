##
## Makefile
## Login : <elthariel@elthariel-desktop>
## Started on  Wed Aug 15 00:42:18 2007 Nahlwe
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

##############################
# Complete this to make it ! #
##############################
NAME 	= test_gtk
SRC	= kbd_view.cc roll_view.cc main.cc
INCL  	= kbd_view.hh roll_view.hh
################
# Optional add #
################
IPATH   = -I.
OBJOPT  = -O3 -g3 -Wall `pkg-config --cflags gtkmm-2.4`        # option for obj
EXEOPT  = -O3 -g3 -Wall  `pkg-config --cflags gtkmm-2.4`      # option for exe (-lefence ...)
LPATH   = -L. `pkg-config --libs gtkmm-2.4`

#####################
# Macro Definitions #
#####################
CC 	= gcc
CXX 	= g++
MAKE 	= make
SHELL	= /bin/sh
OBJS 	= $(SRC:.cc=.o)
RM 	= /bin/rm -f
COMP	= gzip -9v
UNCOMP	= gzip -df
STRIP	= strip

CFLAGS  = $(OBJOPT) $(IPATH)
LDFLAGS = $(EXEOPT) $(LPATH)

.SUFFIXES: .h.Z .c.Z .h.gz .c.gz .c.z .h.z

##############################
# Basic Compile Instructions #
##############################

all:	$(NAME)
$(NAME): $(OBJS) $(SRC) $(INCL)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)
#	$(STRIP) ./$(NAME) # if you debug ,don't strip ...

test : all
	./$(NAME)

depend:
	gcc $(IPATH) -MM $(SRC)
clean:
	-$(RM) $(NAME) $(OBJS) *~
fclean:
	-$(RM) $(NAME)
comp: clean
	$(COMP) $(INCL) $(SRC)
ucomp:
	$(UNCOMP) $(SRC) $(INCL)

check-syntax:
	$(MAKE) syntax-target CFLAGS="-fsyntax-only"

syntax-target: $(CHK_SOURCES:.c=.o)

.c.Z.c .h.Z.h .c.gz.c .h.gz.h .c.z.c .h.z.h :
	 -$(UNCOMP) $<

.c.o:
	$(CC) $(CFLAGS) -c $<
.cc.o:
	$(CXX) $(CFLAGS) -c $<
################
# Dependencies #
################
