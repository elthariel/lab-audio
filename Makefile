#global Makefile for lab-audio

all:
	(cd plugins/tronsonator; make)
	(cd plugins/soulrider; make)
	(cd plugins/butinator; make)
	(cd libs/libthc; make)
