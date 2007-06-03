##
## Makefile.am for zia in /home/elthariel/code/httpd
##
## Made by Nahlwe
## Login   <elthariel@lse.epita.fr>
##
## Started on  Fri Feb 16 04:43:47 2007 Nahlwe
## Last update Sun Jun  3 21:41:38 2007 Nahlwe
##

noinst_HEADERS =

#include_HEADERS = dsp_api.hpp

#######################
# Build an executable #
#######################

INCLUDES = -I $(top_builddir)/

lib_LTLIBRARIES = libdsp.la

libdsp_la_SOURCES = Envelop.cpp iOsc.cc noise.cc varinoise.cc \
	iFilter.cc

# Don't forget that the order of the libraries _does_ matter
libdsp_la_CXXFLAGS = -g -Wall -pthread
libdsp_la_LIBADD =

##########
# Checks #
##########

# --> make check
#TESTS = test-1.sh test-2
#TESTS = test-lfrb test-kbdz
#check_PROGRAMS = test-lfrb test-kbdz
##test_2_SOURCES = main_for_tests.cc
#test_lfrb_SOURCES = test_lfrb.cpp lfringbuffer.cpp
#test_lfrb_CPPFLAGS = -g -Wall -pthread @SIGC_CFLAGS@
#test_lfrb_LDADD = libkbdz.la -lpthread -lrt @SIGC_LIBS@

#test_kbdz_SOURCES = test_kbdz.cpp
#test_kbdz_CPPFLAGS = -g -Wall -pthread @SIGC_CFLAGS@
#test_kbdz_LDADD = libkbdz.la -lpthread -lrt @SIGC_LIBS@

####################
# Additional Rules #
####################

re : clean all

c : clean

a : clean
