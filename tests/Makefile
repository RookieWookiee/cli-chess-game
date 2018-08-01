BASE_DIR 	= $(shell dirname $$(pwd))
TEST_SUFFIX = "_test.c"
TEST_PREFIX = ""
SRCDIR		= src
CC 			= gcc
CFLAGS   	= -Wall -Wextra -ggdb3 -std=gnu99 -iquote $(BASE_DIR) -Wno-unused-parameter
LIBS 		= -lcgreen
TEST_FILES 	= $(shell find . -type f -regex "$(TEST_PREFIX).*$(TEST_SUFFIX)")
SO_OBJS 	= $(shell echo $(TEST_FILES) | sed -e "s/^TEST_PREFIX//g" -e "s/$(TEST_SUFFIX)/.so/g")
VPATH 		= $(shell find $(BASE_DIR)/$(SRCDIR) -type d)

all: $(SO_OBJS)
	-find . -type f -name '*.so' -exec cgreen-runner {} +

%.so: %_test.c %.c
	@echo $@
	@echo $<
	$(CC) -shared -o $@ -fPIC $(CFLAGS) $^ $(LIBS)
