CC=g++
CFLAGS=-lSDL2 -lGL -lGLU -lm -I $(IDIR) -lglfw -lGLEW

IDIR = include
ODIR = obj
SDIR = src

_DEPS =  shader.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = shader.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o main $(SDIR)/main.cpp $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
