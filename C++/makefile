SDIR = src
BINDIR = bin

test: $(SDIR)/ChaCha20.cpp tests/test.cpp $(BINDIR)
	g++ $(SDIR)/ChaCha20.cpp tests/test.cpp -Wall -I $(SDIR) -o $(BINDIR)/test

$(BINDIR):
	@mkdir bin
