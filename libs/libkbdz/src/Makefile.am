##
## Makefile.am for zia in /home/elthariel/code/httpd
##
## Made by Nahlwe
## Login   <elthariel@lse.epita.fr>
##
## Started on  Fri Feb 16 04:43:47 2007 Nahlwe
## Last update Thu Apr  5 12:12:03 2007 Nahlwe
##

noinst_HEADERS = foncteurs.hpp help.hpp \
	thread.hpp lfringbuffer.hh kmain.hh evdev_input.hh \
	kevent.hh iInput.hh iOutput.hh mapping.hh

#include_HEADERS = kbdz_api.hpp

#######################
# Build an executable #
#######################

#INCLUDES = -I $(top_builddir)/src

lib_LTLIBRARIES = libkbdz.la

libkbdz_la_SOURCES = foncteurs.cpp help.cpp thread.cpp \
	lfringbuffer.cpp kmain.cpp evdev_input.cpp iInput.cpp \
	iOutput.cpp aseq_output.cpp mapping.cpp

# Don't forget that the order of the libraries _does_ matter
libkbdz_la_CPPFLAGS = -g -Wall -pthread @SIGC_CFLAGS@
libkbdz_la_LIBADD = -lpthread -lrt -lasound @SIGC_LIBS@

##########
# Checks #
##########

# --> make check
#TESTS = test-1.sh test-2
TESTS = test-lfrb test-kbdz
check_PROGRAMS = test-lfrb test-kbdz
#test_2_SOURCES = main_for_tests.cc
test_lfrb_SOURCES = test_lfrb.cpp lfringbuffer.cpp
test_lfrb_CPPFLAGS = -g -Wall -pthread @SIGC_CFLAGS@
test_lfrb_LDADD = libkbdz.la -lpthread -lrt @SIGC_LIBS@

test_kbdz_SOURCES = test_kbdz.cpp
test_kbdz_CPPFLAGS = -g -Wall -pthread @SIGC_CFLAGS@
test_kbdz_LDADD = libkbdz.la -lpthread -lrt @SIGC_LIBS@

####################
# Additional Rules #
####################

re : clean all

c : clean

a : clean
