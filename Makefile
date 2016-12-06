CC               := gcc
CFLAGS           := -Wall -Werror
GEN_CFLAGS       := -w
EXT_CFLAGS       := -DOUT_OF_TASK
BINDIR           := bin
GENDIR           := gen
GENBINDIR        := bin/gen
FRAMAC           := frama-c
FRAMAC_DFLAGS    := -jessie
FRAMAC_REPLAY    := -jessie-target why3autoreplay
FRAMAC_EFLAGS    := -e-acsl -pp-annot -cpp-extra-args " -C -E -x c $(EXT_CFLAGS) "
FRAMAC_EGEN      := -then-last -print -ocode
FRAMAC_ESHARE    := $(shell frama-c -print-share-path)/e-acsl
FRAMAC_EMSHARE   := $(shell frama-c -print-share-path)/e-acsl/memory_model
FRAMAC_EACSL_LIB := $(FRAMAC_ESHARE)/e_acsl.c $(FRAMAC_EMSHARE)/e_acsl_bittree.c $(FRAMAC_EMSHARE)/e_acsl_mmodel.c


CFLAGS += $(EXT_CFLAGS)

SRCFILES    := $(sort $(shell find . -maxdepth 1 -type f -name '*.c'))
BINFILES    := $(patsubst ./%.c, $(BINDIR)/%,    $(SRCFILES))
GENFILES    := $(patsubst ./%.c, $(GENDIR)/%.c,  $(SRCFILES))
GENBINFILES := $(patsubst $(GENDIR)/%.c,   $(GENBINDIR)/%, $(GENFILES))


all: build

build: $(BINDIR) $(BINFILES)

eacsl: $(GENDIR) $(GENFILES)

eacsl-build: eacsl $(GENBINDIR) $(GENBINFILES) ## Build generated E-ACSL programs.

$(BINDIR):
	@-mkdir -p $(BINDIR)

$(GENDIR):
	@-mkdir -p $(GENDIR)

$(GENBINDIR):
	@-mkdir -p $(GENBINDIR)

$(BINDIR)/%: %.c
	$(CC) $(CFLAGS) $< -o $@

$(GENDIR)/%.c: %.c
	$(FRAMAC) $(FRAMAC_EFLAGS) $< $(FRAMAC_EGEN) $@

$(GENBINDIR)/%: $(GENDIR)/%.c
	$(CC) $(GEN_CFLAGS) $(FRAMAC_EACSL_LIB) $< -o $@

run: build
	@for i in $(BINFILES); do echo $$i; ./$$i; done

eacsl-run: eacsl-build
	@for i in $(GENBINFILES); do echo $$i; ./$$i; done

verify:
	@$(FRAMAC) $(FRAMAC_DFLAGS) $(SRCFILES)

verify-separatedly:
	@for i in $(SRCFILES); do echo $$i; $(FRAMAC) $(FRAMAC_DFLAGS) $$i; done

verify-%:
	@$(FRAMAC) $(FRAMAC_DFLAGS) $*.c

replay:
	@$(FRAMAC) $(FRAMAC_DFLAGS) $(FRAMAC_REPLAY) $(SRCFILES)

replay-separatedly:
	@for i in $(SRCFILES); do echo $$i; $(FRAMAC) $(FRAMAC_DFLAGS) $(FRAMAC_REPLAY) $$i; done

replay-%:
	@$(FRAMAC) $(FRAMAC_DFLAGS) $(FRAMAC_REPLAY) $*.c

clean:
	-rm -fr $(GENBINDIR) $(BINDIR) $(GENDIR)

.PHONY: all build eacsl eacsl-build run eacsl-run verify verify-separatedly replay replay-separatedly clean
