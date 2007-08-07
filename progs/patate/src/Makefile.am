##
## Makefile.am for zia in /home/elthariel/code/httpd
##
## Made by Nahlwe
## Login   <elthariel@lse.epita.fr>
##
## Started on  Fri Feb 16 04:43:47 2007 Nahlwe
## Last update Mon Aug  6 20:17:38 2007 Nahlwe
##

SUBDIRS = seq rt

AM_CPPFLAGS =
CPP_FLAGS =

noinst_HEADERS = lfringbuffer.hh \
	patate_gui.hh patate.hh smp_uint.hh \
	help.hpp patate_gui.hh drumseqview.hh \
	synth_manager.hh \
	midicontroller.hh synthview_generic.hh \
	lv2Manager.hh

#######################
# Build an executable #
#######################

#INCLUDES = -I $(top_builddir)/src

bin_PROGRAMS = patate

patate_SOURCES = foncteurs.cpp \
	lfringbuffer.cpp main.cpp patate.cpp \
	thread.cpp help.cpp patate_gui.cpp drumseqview.cpp \
	synth_manager.cc midicontroller.cc synthview_generic.cc \
	lv2Manager.cc

# Don't forget that the order of the libraries _does_ matter
patate_CPPFLAGS = -g -Wall -pthread @PKG_CFLAGS@ \
	-Iseq/ -I../../../libs/libwef
patate_LDADD = -lpthread -lrt @PKG_LIBS@ seq/libseq.la \
	-L../../../libs/libwef -lwef++ rt/librtsa.la
patate_LDFLAGS =

##########
# Checks #
##########

# --> make check
#TESTS = test-1.sh test-2
TESTS =
check_PROGRAMS = test-lv2

#lv2_inspect.c
test_lv2_SOURCES = test_lv2.c

#lv2Manager.cc patate.cpp \
#	lfringbuffer.cpp synth_manager.cc midicontroller.cc

test_lv2_CFLAGS = -g -Wall -Iseq `pkg-config --cflags libslv2 jack`
test_lv2_LDADD = #seq/libseq.la
test_lv2_LDFLAGS = `pkg-config --libs libslv2 jack`

####################
# Additional Rules #
####################

re : clean all

c : clean

a : clean

ec :
	rm -f *~ \#*\#
