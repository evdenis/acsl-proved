CC            := gcc
CFLAGS        := -Wall -Werror
EXT_CFLAGS    := -DOUT_OF_TASK
BINDIR        := bin
GENDIR        := gen
FRAMAC        := frama-c
FRAMAC_DFLAGS := -jessie

CFLAGS += $(EXT_CFLAGS)

SRCFILES := $(sort $(shell find . -maxdepth 1 -type f -name '*.c'))
BINFILES := $(patsubst ./%.c, $(BINDIR)/%, $(SRCFILES))


all: $(BINDIR) $(BINFILES)

$(BINDIR):
	@-mkdir $(BINDIR)

$(GENDIR):
	@-mkdir $(GENDIR)

$(BINDIR)/%: %.c
	$(CC) $(CFLAGS) $< -o $@

run: $(BINDIR) $(BINFILES)
	@for i in $(BINFILES); do echo $$i; ./$$i; done

verify:
	@$(FRAMAC) $(FRAMAC_DFLAGS) $(SRCFILES)

verify-separatedly:
	@for i in $(SRCFILES); do echo $$i; $(FRAMAC) $(FRAMAC_DFLAGS) $$i; done

verify-%:
	@$(FRAMAC) $(FRAMAC_DFLAGS) $*.c

clean:
	-rm -fr $(BINDIR)

.PHONY: all run verify verify-separatedly clean
