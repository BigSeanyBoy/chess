CFLAGS = -I -Wall

ifeq ($(DEBUG), 1)
	OPTS = -g
endif

CC = clang $(OPTS) $(CFLAGS)

DEPS = position.h display.h test.h

ODIR = obj
_OBJ = main.o position.o test.o display.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<

chess: $(OBJ)
	$(CC) -o $@ $^

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *- core $(INCDIR)/*-