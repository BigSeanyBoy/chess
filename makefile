TARGET = chess

CFLAGS = -g -I./ -I./tests -Wall
CC = clang $(CFLAGS)

ODIR = obj
_OBJ = main.o position.o display.o movegen.o unit.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: main.o position.o display.o movegen.o unit.o $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

main.o:
	$(CC) -c -o obj/main.o main.c

position.o:
	$(CC) -c -o obj/position.o position.c

display.o:
	$(CC) -c -o obj/display.o display.c

movegen.o:
	$(CC) -c -o obj/movegen.o movegen.c

unit.o:
	$(CC) -c -o obj/unit.o tests/unit.c
