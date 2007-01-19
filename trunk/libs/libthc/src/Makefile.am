## Process this file with automake to produce Makefile.in

## Created by Anjuta

#gladedir = $(datadir)/libthc/glade
#glade_DATA = libthc.glade

INCLUDES = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(PACKAGE_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

lib_LTLIBRARIES = libthc.la

libthc_la_SOURCES = \
  skin.cc \
  param.cc \
  skinmanager.cc \
	modemanager.cc \
	cairoutils.cc \
	slider.cc

libthc_la_LDFLAGS =

libthc_la_LIBADD = $(PACKAGE_LIBS) -lboost_filesystem

#EXTRA_DIST = $(glade_DATA)


libthcincludedir = $(includedir)/thc

libthcinclude_HEADERS = \
	thc.h \
	skin.h \
	param.h \
	ithcwidget.h \
	thcwidget.h \
	thcwidget.hxx \
	skinmanager.h \
	modemanager.h \
	cairoutils.h \
	slider.h



