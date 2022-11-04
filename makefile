TARGET = chess

CFLAGS = -g -I./ -Wall
CC = clang $(CFLAGS)

ODIR = obj
_OBJ = chess.o bitboard.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: chess.o bitboard.o $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

chess.o:
	$(CC) -c -o obj/chess.o chess.c

bitboard.o:
	$(CC) -c -o obj/bitboard.o bitboard.c
