# Compilation #
  * compile ll-plugins from http://savannah.nongnu.org/projects/ll-plugins/, to get lv2peg and elven
  * compile jack > 102.6 (with jackmidi)
  * do symlink in debian or ubuntu for jack (otherwise jack apps wont work with the new jack)
  * compile the plugin
  * sudo ./install.sh to install it under /usr/lib/lv2


# Test #
to test it:
elven http://lab-audio.googlecode.com/svn/trunk/plugins/turntable/