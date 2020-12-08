# makefile
TOP_DIR=$(shell pwd)
LIB=libaudio.so
OBJS_DIR=debug/obj
LIB_DIR=debug/lib
CC = gcc
C_FLAGS=
INCLUDE_DIR=-I/usr/include/glib-2.0/

X86_INCLUDE =-I/usr/lib/x86_64-linux-gnu/glib-2.0/include/
X86_LINK_DIR=-L/usr/lib/x86_64-linux-gnu/ -lglib-2.0
ARM_INCLUDE =-I/usr/lib/aarch64-linux-gnu/glib-2.0/include/
ARM_LINK_DIR=-L/usr/lib/aarch64-linux-gnu/ -lglib-2.0
LINK_DIR=
TOP_SOURCE = ${wildcard *.c}
TOP_OBJS = ${patsubst %.c, %.o, $(TOP_SOURCE)}

SUBDIRS=$(shell ls -l | grep ^d | awk '{if($$9 != "debug") if($$9 != "include") print $$9}')
ALLSUBDIRS=$(shell ls -l | grep ^d | awk '{print $$9}')

export CC TOP_DIR LIB LIB_DIR INCLUDE_DIR
.PHONY : all clean
all:prebuild  $(SUBDIRS) $(TOP_OBJS) DEBUG
# all: $(TOP_OBJS) DEBUG
# all: $(SUBDIRS)

prebuild:
    ifeq ("$(platform)", "arm")
        INCLUDE_DIR+=$(ARM_INCLUDE)
	LINK_DIR+=$(ARM_LINK_DIR)
    else
	INCLUDE_DIR+=$(X86_INCLUDE)
	LINK_DIR+=$(X86_LINK_DIR)

    endif
$(SUBDIRS):ECHO
	make -C $@

DEBUG:ECHO
	make -C debug

ECHO:
	@echo $(SUBDIRS)

$(TOP_OBJS):%.o:%.c
	echo $(platform)
	$(CC) $(C_FLAGS) $(INCLUDE_DIR) $(LINK_DIR) -fPIC -c $^ -o $(TOP_DIR)/$(OBJS_DIR)/$@
	#sudo cp ./org.ukui.audio_api.gschema.xml /usr/share/glib-2.0/schemas/
	#sudo cp ./libaudio.so /usr/lib/

clean: subdir_clean
	@-rm -f *.o
	@-rm $(LIB)

subdir_clean:
	@for subdir in $(ALLSUBDIRS); \
    do \
        make -C $$subdir clean; \
    done
