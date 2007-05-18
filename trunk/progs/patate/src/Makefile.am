##
## Makefile.am for zia in /home/elthariel/code/httpd
##
## Made by Nahlwe
## Login   <elthariel@lse.epita.fr>
##
## Started on  Fri Feb 16 04:43:47 2007 Nahlwe
## Last update Fri May 18 13:40:06 2007 Nahlwe
##

SUBDIRS = seq

noinst_HEADERS = Envelop.hh event.hh lfringbuffer.hh \
	patate_gui.hh patate.hh smp_uint.hh \
	help.hpp patate_gui.hh drumseqview.hh noise.hh \
	dsp_config.h iFilter.hh varinoise.hh iSynth.hh \
	drumsynth.hh Envelop.hh synth_manager.hh

#######################
# Build an executable #
#######################

#INCLUDES = -I $(top_builddir)/src

bin_PROGRAMS = patate

patate_SOURCES = AnalogFilter.cpp Envelop.cpp foncteurs.cpp \
	lfringbuffer.cpp main.cpp patate.cpp \
	thread.cpp help.cpp patate_gui.cpp drumseqview.cpp noise.cc \
	iFilter.cc varinoise.cc drumsynth.cc Envelop.cpp \
	synth_manager.cc

# Don't forget that the order of the libraries _does_ matter
patate_CPPFLAGS = -g -Wall -pthread @PKG_CFLAGS@ -Iseq/ -I../../../libs/libwef
patate_LDADD = -lpthread -lrt @PKG_LIBS@ seq/libseq.la -L../../../libs/libwef -lwef++

##########
# Checks #
##########

# --> make check
#TESTS = test-1.sh test-2
#TESTS = test-lfrb test-kbdz
#check_PROGRAMS = test-lfrb test-kbdz
#test_2_SOURCES = main_for_tests.cc
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

ec :
	rm -f *~ \#*\#
