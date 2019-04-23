IDIR =../include
CC=g++
override CFLAGS+=-I$(IDIR) -std=c++14 -O3

ODIR=../src
LDIR =../lib

LIBS=-lm

_OBJ = main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: main

$(ODIR)/main.o: $(ODIR)/main.cpp $(IDIR)/sort.hpp $(IDIR)/printer.hpp $(IDIR)/counter_t.hpp $(IDIR)/dni_t.hpp
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(INCDIR)/*~
