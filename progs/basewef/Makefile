##
## Makefile for basewef gen in /home/elthariel/code/lab-audio/progs/basewef
##
## Made by Nahlwe
## Login   <elthariel@lse.epita.fr>
##
## Started on  Fri Feb  9 13:53:51 2007 Nahlwe
## Last update Fri Feb  9 14:18:40 2007 Nahlwe
##

TARGET					= basewef
OBJS						= mymath.o sin.o trivial_analog.o \
	basewef_maker.o main.o

CFLAGS					= -g -Wall -I../../libs/libwef
LDFLAGS					= -L../../libs/libwef -lwef

all : $(TARGET)

$(TARGET) : $(OBJS)
	gcc -o $(TARGET) $(CFLAGS) $(LDFLAGS) $(OBJS)

.c.o :
	gcc -c $(CFLAGS) $<

clean :
	rm -f $(OBJS) $(TARGET) wefs/*
