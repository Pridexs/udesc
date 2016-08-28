CC=g++
CFLAGS=-lSDL2 -lGL -lGLU -lm -I $(IDIR)

IDIR = include
ODIR = obj
SDIR = src

_DEPS = PTimer.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = PTimer.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o trab_comp_3 $(SDIR)/trab_comp_3.cpp $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o


#OBJS = trab_comp_3.cpp

#CC = g++

#COMPILER_FLAGS = -w

#LINKER_FLAGS = -lSDL2 -lGL -lGLU -lm

#OBJ_NAME = trab_comp_3

#all : $(OBJS)
#	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME) PTimer.cpp
