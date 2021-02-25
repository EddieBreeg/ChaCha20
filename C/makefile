SDIR = src
BINDIR = bin
CARGS = -Wall -I $(SDIR)

all:
	@make test
	@make test2

test: $(SDIR)/ChaCha20.c tests/test.c $(BINDIR)
	gcc $(SDIR)/ChaCha20.c tests/test.c $(CARGS) -o $(BINDIR)/test

test2: $(SDIR)/ChaCha20.c tests/test2.c $(BINDIR)
	gcc $(SDIR)/ChaCha20.c tests/test2.c $(CARGS) -o $(BINDIR)/test2

$(BINDIR):
	@mkdir bin
