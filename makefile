CFLAGS = -I./ -I./tests/ -Wall

ifeq ($(DEBUG), 1)
	OPTS = -g
endif

CC = clang $(OPTS) $(CFLAGS)

DEPS = position.h display.h tests/unit.h

ODIR = obj
_OBJ = main.o position.o display.o
_TOBJ = tests/unit.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ)) $(patsubst ../%,(ODIR)/%,$(_TOBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<

chess: $(OBJ)
	$(CC) -o $@ $^

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *- core $(INCDIR)/*-