LIB = kwiclib/Debug
TEST = kwiclibtest/Debug

SUBPROJECTS = $(LIB) $(TEST)

all: $(SUBPROJECTS)

$(LIB):
	@$(MAKE) -C $@;

$(TEST): $(LIB)
	@$(MAKE) -C $@;

clean:
	@$(MAKE) clean -C $(LIB);
	@$(MAKE) clean -C $(TEST);

test: $(SUBPROJECTS)
	cd $(TEST) && ./kwiclibtest;

.PHONY: $(SUBPROJECTS)
