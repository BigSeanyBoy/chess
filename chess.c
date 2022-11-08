#include "types.h"
#include "bitboard.h"
#include "position.h"
#include "movegen.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
	struct position state;
	char *fenstr = "8/3k4/3pp3/8/5B2/8/1B1p4/1K6 w - - 0 1";
	setpos(&state, fenstr);

	int nbmoves = movegen(&state);
	printf("found %d moves\n", nbmoves);

	return 0;
}
