#include "types.h"
#include "bitboard.h"
#include "position.h"
#include "movegen.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
	struct raylookup rays;
	initrays(&rays);

	struct position state;
	char *fenstr = "4k3/2P4P/8/4Pp2/8/2p1p3/PP1P1PP1/3K4 w - f6 0 1";
	setpos(&state, fenstr);

	U16 movelist[256];
	int nbmoves = movegen(&state, movelist);
	printf("found %d pawn moves\n", nbmoves);

	return 0;
}
