# The name and version of your plugin - edit these (at least the name)
PLUGIN_NAME = promethee
VERSION = 0.1.0

# The lv2peg program - edit if it's not in your path
LV2PEG = lv2peg

# These files go into the bundle
BUNDLE_FILES = manifest.ttl $(PLUGIN_NAME).ttl $(PLUGIN_NAME).so $(PLUGIN_NAME)_gtk.so

# These are the source files for the plugin
PLUGIN_SOURCES = $(PLUGIN_NAME).cpp lv2plugin.cpp lv2instrument.cpp \
	Envelop.cpp Sample.cpp filter.cpp
PLUGIN_HEADERS = lv2plugin.hpp lv2instrument.hpp lv2.h lv2-miditype.h \
	lv2-midifunctions.h $(PLUGIN_NAME).peg frequencytable.hpp Envelop.hh \
	Sample.hh filter.hh
PLUGIN_LDFLAGS = `pkg-config --libs gtkmm-2.4 gthread-2.0 sndfile`
PLUGIN_CFLAGS = -g -Wall `pkg-config --cflags gtkmm-2.4 gthread-2.0 sndfile`

# These are the source files for the plugin GUI
GUI_SOURCES = $(PLUGIN_NAME)_gtk.cpp lv2gtk2gui.cpp
GUI_HEADERS = lv2gtk2gui.hpp lv2-gtk2gui.h $(PLUGIN_NAME).peg
GUI_LDFLAGS = `pkg-config --libs gtkmm-2.4 gthread-2.0`
GUI_CFLAGS = -g -Wall `pkg-config --cflags gtkmm-2.4 gthread-2.0`

# Derived variables - do not edit
PLUGIN_OBJECTS = $(subst .cpp,.o,$(PLUGIN_SOURCES))
GUI_OBJECTS = $(subst .cpp,.o,$(GUI_SOURCES))
ALL_SOURCES = $(sort $(PLUGIN_SOURCES) $(GUI_SOURCES))
ALL_HEADERS = $(sort $(PLUGIN_HEADERS) $(GUI_HEADERS))


# These files go into the distribution
DIST_FILES = Makefile README manifest.ttl $(PLUGIN_NAME).ttl $(ALL_SOURCES) $(ALL_HEADERS)



# Rules start here
all: $(PLUGIN_NAME).lv2

# The main target - the LV2 plugin bundle
$(PLUGIN_NAME).lv2: $(BUNDLE_FILES)
	rm -rf $(PLUGIN_NAME).lv2
	mkdir $(PLUGIN_NAME).lv2
	cp $(BUNDLE_FILES) $(PLUGIN_NAME).lv2

# The plugin module
$(PLUGIN_NAME).so: $(PLUGIN_OBJECTS)
	$(CXX) -shared -fPIC $(LDFLAGS) $(PLUGIN_OBJECTS) $(PLUGIN_LDFLAGS) -o $@

# All the object files for the plugin module
$(PLUGIN_OBJECTS): $(subst .o,.cpp,$@)
	$(CXX) -c -o $@ -fPIC -DPIC $(CFLAGS) $(CXXFLAGS) $(PLUGIN_CFLAGS) $(subst .o,.cpp,$@)

# The plugin GUI module
$(PLUGIN_NAME)_gtk.so: $(GUI_OBJECTS)
	$(CXX) -shared -fPIC $(GUI_OBJECTS) $(LDFLAGS) $(GUI_LDFLAGS) -o $@

# All the object files for the GUI program
$(GUI_OBJECTS): $(subst .o,.cpp,$@)
	$(CXX) -c -o $@ -fPIC -DPIC $(CFLAGS) $(CXXFLAGS) $(GUI_CFLAGS) $(subst .o,.cpp,$@)

# All header dependencies need to be generated and included
-include $(ALL_SOURCES:.cpp=.dep)

# This is how to generate the dependency files
%.dep: %.cpp Makefile
	$(CXX) -M $(CFLAGS) $(CXXFLAGS) $(GUI_CFLAGS) $(subst .dep,.cpp,$@) > $@

# PEG files contain info about the plugin ports
%.peg: %.ttl
	$(LV2PEG) $(subst .peg,.ttl,$@) $@

# The distribution - a bzip2ed tarball
dist: $(DIST_FILES)
	rm -rf $(PLUGIN_NAME)-$(VERSION) $(PLUGIN_NAME)-$(VERSION).tar $(PLUGIN_NAME)-$(VERSION).tar.bz2
	mkdir $(PLUGIN_NAME)-$(VERSION)
	cp $(DIST_FILES) $(PLUGIN_NAME)-$(VERSION)
	tar c $(PLUGIN_NAME)-$(VERSION) > $(PLUGIN_NAME)-$(VERSION).tar
	bzip2 $(PLUGIN_NAME)-$(VERSION).tar
	rm -rf $(PLUGIN_NAME)-$(VERSION)

#install the plugin
install: $(PLUGIN_NAME).lv2
	cp -rf $(PLUGIN_NAME).lv2 /usr/lib/lv2

# Remove all generated files
clean:
	rm -rf $(PLUGIN_NAME).lv2 $(PLUGIN_NAME).so $(PLUGIN_NAME)_gtk.so $(ALL_SOURCES:.cpp=.dep) $(ALL_SOURCES:.cpp=.o)
