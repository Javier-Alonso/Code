IDIR =../include
CC=g++
CFLAGS=-I$(IDIR) -std=c++14 -O3

ODIR=../src
LDIR =../lib

LIBS=-lm

_OBJ = NFA.o cadena_t.o estado_t.o transicion_t.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: NFA

$(ODIR)/transicion_t.o: $(ODIR)/transicion_t.cpp $(IDIR)/transicion_t.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/cadena_t.o: $(ODIR)/cadena_t.cpp $(IDIR)/cadena_t.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/estado_t.o: $(ODIR)/estado_t.cpp $(IDIR)/estado_t.h $(IDIR)/transicion_t.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/NFA.o: $(ODIR)/NFA.cpp $(IDIR)/NFA.h $(IDIR)/estado_t.h $(IDIR)/cadena_t.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/main.o: $(ODIR)/main.cpp $(IDIR)/NFA.h
	$(CC) -c -o $@ $< $(CFLAGS)

NFA: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(INCDIR)/*~
