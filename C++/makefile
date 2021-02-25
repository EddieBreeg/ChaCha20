SDIR = src
BINDIR = bin

all:
	make test
	make test2

test: $(SDIR)/ChaCha20.cpp tests/test.cpp $(BINDIR)
	g++ $(SDIR)/ChaCha20.cpp tests/test.cpp -Wall -I $(SDIR) -o $(BINDIR)/test

test2: $(SDIR)/ChaCha20.cpp tests/test2.cpp $(BINDIR)
	g++ $(SDIR)/ChaCha20.cpp tests/test2.cpp -Wall -I $(SDIR) -o $(BINDIR)/test2

$(BINDIR):
	@mkdir bin
