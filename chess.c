#include "types.h"
#include "bitboard.h"
#include "position.h"
#include "movegen.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
	struct raylookup rays;
	initrays(&rays);

	struct position state;
	char *fenstr = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	setpos(&state, fenstr);

	U16 movelist[256];
	int nbmoves = movegen(&state, movelist);
	printf("found %d moves\n", nbmoves);

	return 0;
}
