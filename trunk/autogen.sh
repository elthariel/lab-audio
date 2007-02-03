#!/bin/sh
# Run this to generate all the initial makefiles, etc.
#!/bin/sh

top=`pwd`

echo 'Generating necessary files (recursively)...'

aclocal &

autogen_dir() {
	dir=$1
	name=$2
	echo -ne $name
	cd $dir
	./autogen.sh
	cd ..
}

#autogen_dir libs/libthc "* libthc * \t"
#autogen_dir plugins "* plugins * \t"

automake --foreign --add-missing
autoconf
