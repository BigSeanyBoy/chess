#include "types.h"
#include "bitboard.h"
#include "position.h"
#include "movegen.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
	struct position state;
	char *fenstr = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	setpos(&state, fenstr);

	U16 move = E4 | (E2 << 6);
	make(move, &state);

	return 0;
}
