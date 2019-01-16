IDIR =../include
CC=g++
CFLAGS=-I$(IDIR) -std=c++14 -O3

ODIR=../src
LDIR =../lib

LIBS=-lm

_OBJ = tuple_t.o tape_t.o TuringMachine.o  main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: TM

$(ODIR)/tuple_t.o: $(ODIR)/tuple_t.cpp $(IDIR)/tuple_t.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/tape_t.o: $(ODIR)/tape_t.cpp $(IDIR)/tape_t.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/TuringMachine.o: $(ODIR)/TuringMachine.cpp $(IDIR)/TuringMachine.h $(IDIR)/tuple_t.h $(IDIR)/tape_t.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/main.o: $(ODIR)/main.cpp $(IDIR)/TuringMachine.h
	$(CC) -c -o $@ $< $(CFLAGS)

TM: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(INCDIR)/*~
