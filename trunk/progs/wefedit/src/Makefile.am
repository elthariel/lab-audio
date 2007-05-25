##
## Makefile.am for zia in /home/elthariel/code/httpd
##
## Made by Nahlwe
## Login   <elthariel@lse.epita.fr>
##
## Started on  Fri Feb 16 04:43:47 2007 Nahlwe
## Last update Fri May 25 17:16:27 2007 Elthariel
##

AM_CPPFLAGS =
CPP_FLAGS =

noinst_HEADERS = main_win.hh

#######################
# Build an executable #
#######################

#INCLUDES = -I $(top_builddir)/src

bin_PROGRAMS = wefedit

wefedit_SOURCES = main_win.cc main.cc

# Don't forget that the order of the libraries _does_ matter
wefedit_CPPFLAGS = -g -Wall -O3 -pthread @PKG_CFLAGS@ \
	-Iseq/ -I../../../libs/libwef
wefedit_LDADD = -lpthread -lrt @PKG_LIBS@ \
	-L../../../libs/libwef -lwef++
wefedit_LDFLAGS = -O3

##########
# Checks #
##########

# --> make check

#TESTS = test-noise
#check_PROGRAMS = test-noise
#
#test_noise_SOURCES = noise_test.cc drumsynth.cc \
#	noise.cc iFilter.cc varinoise.cc
#test_noise_CPPFLAGS = -g -Wall

####################
# Additional Rules #
####################

re : clean all

c : clean

a : clean

ec :
	rm -f *~ \#*\#
