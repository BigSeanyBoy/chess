TARGET = chess

CFLAGS = -g -I./ -I./tests -Wall
CC = clang $(CFLAGS)

ODIR = obj
_OBJ = chess.o bitboard.o targets.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: chess.o bitboard.o targets.o $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

chess.o:
	$(CC) -c -o obj/chess.o chess.c

bitboard.o:
	$(CC) -c -o obj/bitboard.o bitboard.c

targets.o:
	$(CC) -c -o obj/targets.o tests/targets.c
