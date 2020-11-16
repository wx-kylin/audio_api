OBJS=*.o
ODIR=obj
C_FLAGS=-shared

$(TOP_DIR)/$(LIB_DIR)/$(LIB):$(ODIR)/$(OBJS)
	$(CC) $(INCLUDE_DIR) $(C_FLAGS) -o $@ $^
	cp $@ $(TOP_DIR)

clean:
	@-rm -f *.o
	@-rm -f obj/*
	@-rm -f lib/*
