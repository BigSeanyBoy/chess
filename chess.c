#include "types.h"
#include "bitboard.h"
#include "position.h"
#include "movegen.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
	struct position state;
	char *fenstr = "rnbqkbnr/ppp1pppp/8/8/3pP3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1";
	setpos(&state, fenstr);

	U16 move = E3 | (D4 << 6) | EN_PASSANT;
	make(move, &state);

	return 0;
}
