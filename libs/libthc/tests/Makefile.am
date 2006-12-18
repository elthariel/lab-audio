## Process this file with automake to produce Makefile.in

## Created by Anjuta

#gladedir = $(datadir)/clochette/glade
#glade_DATA = clochette.glade

INCLUDES = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(PACKAGE_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = thcmeter

thcmeter_SOURCES = \
	main.cc



thcmeter_LDADD = $(PACKAGE_LIBS)
thcmeter_DEPENDENCIES = ../src/libthc.la
#thcmeter_CXXFLAGS = -DMONOLITHIC_INGENUITY -DGTK_DISABLE_DEPRECATED -DGDK_DISABLE_DEPRECATED -I../../ingenuity -I../../../common -I../../../libs -I../../../libs/client -DPKGDATADIR=\"$(pkgdatadir)\"
thcmeter_LDADD += ../src/libthc.la
#thcmeter_LDFLAGS = -L../../../libs/client/.libs -L../../../libs/engine/.libs

#EXTRA_DIST = $(glade_DATA)
