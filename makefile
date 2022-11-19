TARGET = chess

CFLAGS = -g -I./ -I./tests -Wall
CC = clang $(CFLAGS)

ODIR = obj
_OBJ = chess.o bitboard.o position.o movegen.o uci.o search.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: chess.o bitboard.o position.o movegen.o uci.o search.o $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

chess.o:
	$(CC) -c -o obj/chess.o chess.c

bitboard.o:
	$(CC) -c -o obj/bitboard.o bitboard.c

position.o:
	$(CC) -c -o obj/position.o position.c

movegen.o:
	$(CC) -c -o obj/movegen.o movegen.c

uci.o:
	$(CC) -c -o obj/uci.o uci.c

search.o:
	$(CC) -c -o obj/search.o search.c
