##
## Makefile for libwef in /home/elthariel/code/lab-audio/libs/libwef
##
## Made by Nahlwe
## Login   <elthariel@epita.fr>
##
## Started on  Fri Feb  9 13:40:59 2007 Nahlwe
## Last update Fri Feb  9 15:39:17 2007 Nahlwe
##

CC							= gcc

OBJS						= wef_mem_0_2.o wef.o
TARGET					= libwef.so

CFLAGS					= -g -Wall
LDFLAGS					=

all : $(TARGET)

$(TARGET) : $(OBJS)
	gcc -o $(TARGET) -shared $(CFLAGS) $(LDFLAGS) $(OBJS)

.c.o:
	gcc -c $(CFLAGS) $<

.cpp.o:
	g++ -c $(CFLAGS) $<

clean:
	rm -f $(OBJS) $(TARGET)

install: $(TARGET)
	cp -f $(TARGET) /usr/lib

uninstall:
	rm -f /usr/lib/$(TARGET)

