CC=g++
CFLAGS=-I $(IDIR)

IDIR = include
ODIR = obj
SDIR = src

_DEPS = Middleware.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Middleware.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o authclient $(SDIR)/authclient.cpp $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
