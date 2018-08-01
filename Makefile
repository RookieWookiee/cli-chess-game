SHELL = /bin/bash
CC = cc
TARGET = chess
SRCDIR = src
TESTDIR = tests
CFLAGS  = -Wall -Wextra -ggdb3 -std=gnu99 -iquote . -Wno-unused-parameter
SRCS = $(shell find src/ -type f -name '*.c' | sort)
DEPDIR = deps

DEPS = $(shell echo $(SRCS) | sed -e 's/$(SRCDIR)/$(DEPDIR)/g' -e 's/\.c/\.d/g')

OBJDIR = obj
OBJS = $(shell find src/ -type f -name '*.c' | sort | sed -e 's/src/$(OBJDIR)/' -e 's/.c$$/.o/')

all: $(TARGET)

-include $(DEPS)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJS): | $(OBJDIR)

$(DEPS): | $(DEPDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	@# Get user defined header dependencies and put them in a .d file inside DEPDIR
	@$(CC) $(CFLAGS) -MM -MP -MG -MT "$(shell echo $< | sed -e 's/^$(SRCDIR)/$(OBJDIR)/' -e 's/\.c$$/\.o/')" -c $< -o "$(shell echo $@ | sed -e 's/^$(OBJDIR)/$(DEPDIR)/' -e 's/\.o$$/\.d/')"

$(OBJDIR):
	@-for i in `find src/ -type d`; do dir=`echo $$i | sed -e 's/src/$(OBJDIR)/'`; test ! -d $$dir && mkdir -p $$dir; done

$(DEPDIR):
	@-for i in `find src/ -type d`; do dir=`echo $$i | sed -e 's/src/$(DEPDIR)/'`; test ! -d $$dir && mkdir -p $$dir; done

clean:
	-rm -r obj/
	-rm chess
	-find $(TESTDIR) -type f -name '*.so' -exec rm {} \;

check:
	-cd $(TESTDIR) && $(MAKE)

.PHONY: clean check
