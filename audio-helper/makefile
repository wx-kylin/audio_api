# makefile
MY_DIR=$(shell pwd)
BIN=main
LIBDIR=$(MY_DIR)/../lib-audio-helper/
LIBNAME=audio
CC = gcc
INCLUDE_DIR=-I/usr/include/glib-2.0/
INCLUDE_DIR+=-I/usr/lib/x86_64-linux-gnu/glib-2.0/include/
# LINK_DIR=-L$(LIBDIR) -l$(LIBNAME) -L/usr/lib/x86_64-linux-gnu/ -lglib-2.0 -lgio-2.0
LINK_DIR=-L/usr/lib/ -laudio -L/usr/lib/x86_64-linux-gnu/ -lglib-2.0 -lgio-2.0

TOP_SOURCE = ${wildcard *.c}

SUBDIRS=

.PHONY : all clean
all:
	@echo $(LIBDIR)
	$(CC) $(INCLUDE_DIR) -o $(BIN) $(TOP_SOURCE) $(LINK_DIR)

clean:
	@-rm -f *.o
	@-rm $(BIN)
