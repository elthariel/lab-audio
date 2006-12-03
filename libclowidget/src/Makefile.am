## Process this file with automake to produce Makefile.in

## Created by Anjuta

gladedir = $(datadir)/libclowidget/glade
glade_DATA = libclowidget.glade

INCLUDES = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(PACKAGE_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

lib_LTLIBRARIES = libclowidget.la

libclowidget_la_SOURCES = \
	main.cc

libclowidget_la_LDFLAGS =

libclowidget_la_LIBADD = $(PACKAGE_LIBS)

EXTRA_DIST = $(glade_DATA)
