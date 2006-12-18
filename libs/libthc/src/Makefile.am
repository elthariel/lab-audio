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
	slider.cc
#	CloExpander.cpp \
#	shapereditor.cpp \
#	keyboard.cpp \
#	envelopeeditor.cpp \
#	vgknob.cpp \
#	pdeditor.cpp

libthc_la_LDFLAGS =

libthc_la_LIBADD = $(PACKAGE_LIBS)

EXTRA_DIST = $(glade_DATA)


libthcincludedir = $(includedir)/thc

libthcinclude_HEADERS = \
	thc.h \
	skin.h \
	param.h \
	widget.h \
	slider.h

#	CloExpander.h \
#	shapereditor.hpp \
#	keyboard.hpp \
#	envelopeeditor.hpp \
#	vgknob.hpp \
#	pdeditor.hpp
	
	
	
	
