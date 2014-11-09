PROG = kwic/Debug
LIB = kwiclib/Debug
TEST = kwiclibtest/Debug

SUBPROJECTS = $(LIB) $(TEST) $(PROG)

all: $(SUBPROJECTS)

$(LIB):
	@$(MAKE) -C $@;

$(TEST): $(LIB)
	@$(MAKE) -C $@;

$(PROG): $(LIB)
	@$(MAKE) -C $@;

clean:
	@$(MAKE) clean -C $(LIB);
	@$(MAKE) clean -C $(TEST);
	@$(MAKE) clean -C $(PROG);

test: $(SUBPROJECTS)
	cd $(TEST) && ./kwiclibtest;

.PHONY: $(SUBPROJECTS)
