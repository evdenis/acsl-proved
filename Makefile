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

all: build ## Default target. Build each program.

build: $(BINDIR) $(BINFILES) ## Build each program.

eacsl: $(GENDIR) $(GENFILES) ## Generate E-ACSL programs.

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

run: build ## Run each program. You can also type run-<target>.
	@for i in $(BINFILES); do echo $$i; ./$$i; done

run-%: $(BINDIR) $(BINDIR)/%
	$(BINDIR)/$*

eacsl-run: eacsl-build ## Run each E-ACSL program. You can also type eacsl-run-<target>.
	@for i in $(GENBINFILES); do echo $$i; ./$$i; done

eacsl-run-%: $(GENDIR) $(GENBINDIR) $(GENBINDIR)/%
	$(GENBINDIR)/$*

verify: ## Run Frama-C on all files simultaneously. You can also type verify-<target>.
	@$(FRAMAC) $(FRAMAC_DFLAGS) $(SRCFILES)

verify-separatedly: ## Run Frama-C on each file consequently.
	@for i in $(SRCFILES); do echo $$i; $(FRAMAC) $(FRAMAC_DFLAGS) $$i; done

verify-%:
	@$(FRAMAC) $(FRAMAC_DFLAGS) $*.c

replay: ## Replay proofs simultaiously. You can also type replay-<target>.
	@$(FRAMAC) $(FRAMAC_DFLAGS) $(FRAMAC_REPLAY) $(SRCFILES)

replay-separatedly: ## Replay proofs consequently.
	@for i in $(SRCFILES); do echo $$i; $(FRAMAC) $(FRAMAC_DFLAGS) $(FRAMAC_REPLAY) $$i; done

replay-%:
	@$(FRAMAC) $(FRAMAC_DFLAGS) $(FRAMAC_REPLAY) $*.c

clean: ## Remove all binary and generated files.
	-rm -fr $(GENBINDIR) $(BINDIR) $(GENDIR)

.PHONY: all build eacsl eacsl-build run eacsl-run verify verify-separatedly replay replay-separatedly clean

#COLORS
GREEN  := $(shell tput -Txterm setaf 2)
WHITE  := $(shell tput -Txterm setaf 7)
YELLOW := $(shell tput -Txterm setaf 3)
RESET  := $(shell tput -Txterm sgr0)

# Add the following 'help' target to your Makefile
# And add help text after each target name starting with '\#\#'
# A category can be added with @category
HELP_FUN = \
    %help; \
    while(<>) { push @{$$help{$$2 // 'options'}}, [$$1, $$3] if /^([a-zA-Z\-]+)\s*:.*\#\#(?:@([a-zA-Z\-]+))?\s(.*)$$/ }; \
    print "usage: make [target]\n\n"; \
    for (sort keys %help) { \
    print "${WHITE}$$_:${RESET}\n"; \
    for (@{$$help{$$_}}) { \
    $$sep = " " x (32 - length $$_->[0]); \
    print "  ${YELLOW}$$_->[0]${RESET}$$sep${GREEN}$$_->[1]${RESET}\n"; \
    }; \
    print "\n"; }

help: ## Show this help.
	@perl -e '$(HELP_FUN)' $(MAKEFILE_LIST)

.PHONY: help
