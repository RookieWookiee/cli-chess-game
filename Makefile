SHELL = /bin/bash
CC = cc
TARGET = chess
SRCDIR = src
UTILSDIR = utils
TESTDIR = tests
BASEDIR = $(shell pwd)
CFLAGS  = -Wall -Wextra -ggdb3 -std=c99 -iquote $(BASEDIR) -Wno-unused-parameter
SRCS = $(shell find $(SRCDIR) $(UTILSDIR) -type f -name '*.c' | sort)
DEPDIR = deps

DEPS = $(shell find $(DEPDIR) -type f -name '*.d')

OBJDIR = obj
OBJS = $(shell find $(BASEDIR)/$(SRCDIR) $(BASEDIR)/$(UTILSDIR) -type f -name '*.c' | sort | sed -e 's,/$(SRCDIR)/,/$(OBJDIR)/,g' -e 's,/$(UTILSDIR)/,/$(OBJDIR)/,' | sed -e 's/.c$$/.o/')

.PHONY: clean check all debug

all: $(TARGET)

debug:
	@echo $(CFLAGS)
	cd $(UTILSDIR) && $(MAKE) CFLAGS="$(CFLAGS)" debug

$(TARGET): $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo Build finished. Target updated.

$(OBJS): | $(OBJDIR) $(DEPDIR)

$(OBJS):
	@cd $(SRCDIR) && $(MAKE) -j DIRNAME=$(SRCDIR) CC="$(CC)" CFLAGS="$(CFLAGS)"
	@cd $(UTILSDIR) && $(MAKE) -j DIRNAME=$(UTILSDIR) CC="$(CC)" CFLAGS="$(CFLAGS)"

%.o: | $(OBJDIR) $(DEPDIR)
# you should not be here
	@echo $@

$(OBJDIR):
	@echo "Generation obj/ folder structure for object files"
	@-for i in `find $(SRCDIR)/ $(UTILSDIR)/ -type d`; do dir=`echo $$i | sed -e 's/src/$(OBJDIR)/'`; test ! -d $$dir && mkdir -p $$dir; done

$(DEPDIR):
	@echo "Generation deps/ folder structure for file depedencies"
	@-for i in `find $(SRCDIR)/ $(UTILSDIR)/ -type d`; do dir=`echo $$i | sed -e 's/src/$(DEPDIR)/'`; test ! -d $$dir && mkdir -p $$dir; done

clean:
	-rm -r obj/
	-rm -r deps/
	-find $(TESTDIR) -type f -name '*.so' -exec rm {} \;

check: $(OBJS)
	@-cd $(TESTDIR) && $(MAKE) -j FAIL_FAST=$(FAIL_FAST) CC=$(CC)

-include $(DEPS)
