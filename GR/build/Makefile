IDIR =../include
CC=g++
CFLAGS=-I$(IDIR) -std=c++14 -O3

ODIR=../src
LDIR =../lib

LIBS=-lm

_OBJ = GR_t.o  main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: GR

$(ODIR)/GR_t.o: $(ODIR)/GR_t.cpp $(IDIR)/GR_t.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/main.o: $(ODIR)/main.cpp $(IDIR)/GR_t.h
	$(CC) -c -o $@ $< $(CFLAGS)

GR: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(INCDIR)/*~
