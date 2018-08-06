BASEDIR		= $(shell dirname $$(pwd))
TEST_SUFFIX = "_test.c"
TEST_PREFIX = ""
SRCDIR		= src
CC 			= gcc
CFLAGS   	= -Wall -Wextra -ggdb3 -std=c99 -iquote $(BASEDIR) -Wno-unused-parameter
LIBS 		= -lcgreen
TEST_FILES 	= $(shell find . -type f -regex "$(TEST_PREFIX).*$(TEST_SUFFIX)")
SO_OBJS 	= $(shell echo $(TEST_FILES) | sed -e "s/^TEST_PREFIX//g" -e "s/$(TEST_SUFFIX)/.so/g")
VPATH 		= $(shell find $(BASEDIR)/$(SRCDIR) -type d)

UTILS_OBJS 	= $(shell find $(BASEDIR)/utils -type f -name '*.c' | sed -e 's,\.c,\.o,g' -e 's,/utils/,/obj/,g')
DEPS = $(shell find $(BASEDIR)/deps -type f -name '*.d')

.PHONY: all rebuild_utils

all: rebuild_utils $(SO_OBJS)
ifeq ($(FAIL_FAST), yes)
	for test_file in $(shell find -type f -name '*.so'); do \
		cgreen-runner $$test_file; \
		if (( $$? != 0 )); then \
			break; \
		fi \
	done
else
	for test_file in $(shell find -type f -name '*.so'); do \
		cgreen-runner $$test_file; \
	done
endif

rebuild_utils:
	cd $(BASEDIR)/utils && $(MAKE) DIRNAME=utils

%/obj/%.o:
	cd ../utils/ && $(MAKE) DIRNAME=utils

debug:
	@echo $(FAIL_FAST)

%.so: %_test.c %.c $(UTILS_OBJS)
	$(CC) -shared -o $@ -fPIC $(CFLAGS) $^ $(LIBS)

%.so:
	$(CC) -shared -o $@ -fPIC $(CFLAGS) $^ $(UTILS_OBJS) $(LIBS)

-include $(DEPS)
