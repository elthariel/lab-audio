##
## Makefile.am for zia in /home/elthariel/code/httpd
##
## Made by Nahlwe
## Login   <elthariel@lse.epita.fr>
##
## Started on  Fri Feb 16 04:43:47 2007 Nahlwe
## Last update Tue May 29 22:07:58 2007 Nahlwe
##

SUBDIRS = seq

AM_CPPFLAGS =
CPP_FLAGS =

noinst_HEADERS = Envelop.hh event.hh lfringbuffer.hh \
	patate_gui.hh patate.hh smp_uint.hh \
	help.hpp patate_gui.hh drumseqview.hh noise.hh \
	dsp_config.h iFilter.hh varinoise.hh iSynth.hh \
	drumsynth.hh Envelop.hh synth_manager.hh \
	midicontroller.hh synthview_generic.hh \
	lv2Manager.hh

#######################
# Build an executable #
#######################

#INCLUDES = -I $(top_builddir)/src

bin_PROGRAMS = patate

patate_SOURCES = AnalogFilter.cpp Envelop.cpp foncteurs.cpp \
	lfringbuffer.cpp main.cpp patate.cpp \
	thread.cpp help.cpp patate_gui.cpp drumseqview.cpp noise.cc \
	iFilter.cc varinoise.cc drumsynth.cc \
	synth_manager.cc midicontroller.cc synthview_generic.cc \
	lv2Manager.cc

# Don't forget that the order of the libraries _does_ matter
patate_CPPFLAGS = -g -Wall -pthread @PKG_CFLAGS@ \
	-Iseq/ -I../../../libs/libwef
patate_LDADD = -lpthread -lrt @PKG_LIBS@ seq/libseq.la \
	-L../../../libs/libwef -lwef++
patate_LDFLAGS =

##########
# Checks #
##########

# --> make check
#TESTS = test-1.sh test-2
TESTS = test-noise
check_PROGRAMS = test-noise test-lv2

test_noise_SOURCES = noise_test.cc drumsynth.cc \
	noise.cc iFilter.cc varinoise.cc
test_noise_CPPFLAGS = -g -Wall

test_lv2_SOURCES = test_lv2.cc lv2Manager.cc patate.cpp \
	lfringbuffer.cpp synth_manager.cc midicontroller.cc

test_lv2_CPPFLAGS = -g -Wall -pthread @PKG_CFLAGS@ -Iseq
test_lv2_LDADD = @PKG_LIBS@ seq/libseq.la

####################
# Additional Rules #
####################

re : clean all

c : clean

a : clean

ec :
	rm -f *~ \#*\#
