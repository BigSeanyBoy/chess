CFLAGS = -I -Wall

ifeq ($(DEBUG),1)
	OTPS = -g
endif

CC = clang $(OPTS) $(CFLAGS)

DEPS = position.h movegen.h fen.h display.h

ODIR = obj
_OBJ = main.o movegen.o fen.o display.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<

chess: $(OBJ)
	$(CC) -o $@ $^

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *- core $(INCDIR)/*-