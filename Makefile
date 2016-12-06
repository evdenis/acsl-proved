CC         := gcc
CFLAGS     := -Wall -Werror
EXT_CFLAGS := -DOUT_OF_TASK
BINDIR     := bin

CFLAGS += $(EXT_CFLAGS)

BINFILES := $(sort $(shell find . -maxdepth 1 -type f -name '*.c'))
BINFILES := $(patsubst ./%.c, $(BINDIR)/%, $(BINFILES))


all: $(BINDIR) $(BINFILES)

$(BINDIR):
	-mkdir $(BINDIR)

$(BINDIR)/%: %.c
	$(CC) $(CFLAGS) $< -o $@

run: $(BINDIR) $(BINFILES)
	@for i in $(BINFILES); do echo $$i; ./$$i; done

clean:
	rm -fr $(BINDIR)

.PHONY: all clean
