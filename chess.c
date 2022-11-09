#include "types.h"
#include "bitboard.h"
#include "position.h"
#include "movegen.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
	struct position state;
	char *fenstr = "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1";
	setpos(&state, fenstr);

	gendriver(&state);
	printf("found %d moves\n", state.moves.count);

	return 0;
}
