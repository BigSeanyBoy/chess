#include "types.h"
#include "bitboard.h"
#include "position.h"
#include "movegen.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
	struct position state;
	char *fenstr = "2k5/1p6/8/4p1R1/8/8/K7/1R6 w - - 0 1";
	setpos(&state, fenstr);

	int nbmoves = movegen(&state);
	printf("found %d moves\n", nbmoves);

	return 0;
}
