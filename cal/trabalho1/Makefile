CC=g++
CFLAGS=-lm -I $(IDIR)

IDIR = include
ODIR = obj
SDIR = src

_DEPS = heapsort.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = heapsort.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o main $(SDIR)/main.cpp $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
