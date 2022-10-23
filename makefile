CC = clang
CFLAGS = -I -Wall

DEPS = board.h fen.h display.h

ODIR = obj
_OBJ = main.o board.o fen.o display.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

chess: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *- core $(INCDIR)/*-