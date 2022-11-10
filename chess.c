#include "types.h"
#include "bitboard.h"
#include "position.h"
#include "movegen.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
	struct position state;
	char *fenstr = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/R3KBNR w KQkq - 0 1";
	setpos(&state, fenstr);

	U16 move = C1 | (E1 << 6) | CASTLING;
	make(move, &state);

	return 0;
}
