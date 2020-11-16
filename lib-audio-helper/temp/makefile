# SUBDIR'S MAKEFILE SHOULD BE LIKE THIS
MY_DIR=$(shell pwd)
INCLUDE_DIR=
C_FLAGS=

SUBDIRS=$(shell ls -l | grep ^d | awk '{print $$9}')

CUR_SOURCE=${wildcard *.c}
CUR_OBJS=${patsubst %.c, %.o, $(CUR_SOURCE)}

all:$(SUBDIRS) $(CUR_OBJS)

$(SUBDIRS):ECHO
	make -C $@

$(CUR_OBJS):%.o:%.c
	# $(CC) $(INCLUDE_DIR) $(C_FLAGS) -c $^ -o $(TOP_DIR)/$(OBJS_DIR)/$@
	$(CC) $(INCLUDE_DIR) $(C_FLAGS) -c $^ -o $@

ECHO:
	@echo $(SUBDIRS)

clean: subdir_clean
	@-rm -f *.o

subdir_clean:
	@for subdir in $(SUBDIRS); \
    do \
        make -C $$subdir clean; \
    done