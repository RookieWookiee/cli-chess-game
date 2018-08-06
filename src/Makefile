# Important Note: this file is hard linked into utils/ and src/

DIRNAME = $(shell basename $$(pwd))
CC = cc
CFLAGS = -Wall -Wextra -ggdb3 -std=gnu99 -iquote $(BASEDIR) -Wno-unused-parameter
VPATH = ../

BASEDIR = $(shell dirname $$(pwd))
SRCS = $(shell find $(BASEDIR)/$(DIRNAME) -type f -name '*.c' | sort)

DEPDIR_NAME = deps
DEPDIR = $(BASEDIR)/$(DEPDIR_NAME)
DEPS = $(shell echo $(SRCS) | sed -e 's,$(DIRNAME),$(DEPDIR_NAME),g' -e 's/\.c/\.d/g')

OBJDIR_NAME = obj
OBJDIR = $(BASEDIR)/$(OBJDIR_NAME)
OBJS = $(shell find $(BASEDIR)/$(DIRNAME) -type f -name '*.c' | sort | sed -e 's,/$(DIRNAME)/,/$(OBJDIR_NAME)/,' | sed -e 's/.c$$/.o/')

SRCDIR = src

all: $(OBJS)

debug:
	@echo $(CFLAGS)

$(OBJDIR)/%.o: $(DIRNAME)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	@# Get user defined header dependencies and put them in a .d file inside $DEPDIR
	@$(CC) $(CFLAGS) -MM -MP -MG -MT $(OBJDIR)/$(shell echo $(@F) | sed -e 's/\.c$$/\.o/') -c $< -o $(shell echo $@ | sed -e 's,$(OBJDIR_NAME),$(DEPDIR_NAME),' -e 's,\.o$$,\.d,')

	@sed -i -e 's,$<,$(shell echo $< | sed 's,../,$(BASEDIR)/,'),' $(DEPDIR)/$(shell echo $< | sed -e 's,\.c,\.d,' -e 's,\.\./$(DIRNAME)/,,')

$(OBJS): | $(OBJDIR)

$(DEPS): | $(DEPDIR)

$(OBJDIR):
	@echo Generating object directory structure...
	@-for i in `find ./ -type d`; do dir=`echo $$i | sed -e 's/.\//$(OBJDIR_NAME)\//'`; test ! -d $(BASEDIR)/$$dir && mkdir -p $(BASEDIR)/$$dir; done

$(DEPDIR):
	@echo Generating file dependency directory structure...
	@-for i in `find ./ -type d`; do dir=`echo $$i | sed -e 's/.\//$(DEPDIR_NAME)\//'`; test ! -d $(BASEDIR)/$$dir && mkdir -p $(BASEDIR)/$$dir; done

-include $(DEPS)

.PHONY: all
