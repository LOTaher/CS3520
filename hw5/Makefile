CC = g++
CFLAGS = -I$(IDIR) -g -std=c++11 -O0

IDIR = .
ODIR = .

LIBS = -lncurses

_DEPS = ant.hpp cell.hpp critter.hpp doodlebug.hpp game.hpp grid.hpp queenant.hpp workerant.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))


_OBJ = ant.o cell.o critter.o doodlebug.o game.o grid.o queenant.o workerant.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


hw5: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


.PHONY: clean
clean:
	rm -f $(ODIR)/*.o hw5


.PHONY: etags
etags:
	find . -type f -iname "*.[ch]" | xargs etags --append
