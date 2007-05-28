##
## Makefile for libwef in /home/elthariel/code/lab-audio/libs/libwef
##
## Made by Nahlwe
## Login   <elthariel@epita.fr>
##
## Started on  Fri Feb  9 13:40:59 2007 Nahlwe
## Last update Fri May 25 11:15:34 2007 Elthariel
##

CC					= gcc

OBJS					= wef_mem_0_2.o wef.o
TARGET					= libwef

CFLAGS					= -g -Wall -fPIC
LDFLAGS					=

all : $(TARGET)

$(TARGET) : $(OBJS)
	gcc -o $(TARGET).so -shared $(CFLAGS) $(LDFLAGS) wef_mem_0_2.o
	g++ -o $(TARGET)++.so -shared $(CFLAGS) $(LDFLAGS) wef_mem_0_2.o wef.o

.c.o:
	gcc -c $(CFLAGS) $<

.cpp.o:
	g++ -c $(CFLAGS) $<

clean:
	rm -f $(OBJS) $(TARGET)++.so $(TARGET).so

install: $(TARGET)
	cp -f $(TARGET).so $(TARGET)++.so /usr/lib

uninstall:
	rm -f /usr/lib/$(TARGET)

c : clean
