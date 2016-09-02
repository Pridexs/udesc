CC=g++
CFLAGS=-lSDL2 -lGL -lGLU -lm -I $(IDIR)

IDIR = include
ODIR = obj
SDIR = src

_DEPS = PTimer.h PRain.h POriginal.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = PTimer.o PRain.o POriginal.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o trab_comp_3 $(SDIR)/trab_comp_3.cpp $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
