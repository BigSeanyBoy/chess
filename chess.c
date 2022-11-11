#include "types.h"
#include "bitboard.h"
#include "position.h"
#include "movegen.h"

#include <stdio.h>

U64 perft(struct position *state, int depth) {
	U16 movelist[256];

	if (depth == 0 && !incheck(state)) {
		return 1ull;
	}

	int count = gendriver(state, movelist);
	struct position statecopy;
	U64 nodes = 0;
	for (int i = 0; i < count; ++i) {
		copy(state, &statecopy);
		make(movelist[i], &statecopy);
		U64 enemybb = statecopy.boards[flip(statecopy.side)];
		if ((statecopy.boards[KING] & enemybb) == 0) {
			return 0ull;
		}
		nodes += perft(&statecopy, depth - 1);
	}
	
	return nodes;
}

int main(int argc, char *argv[]) {
	struct position state;
	char *fenstr = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	setpos(&state, fenstr);

	printf("%llu\n", perft(&state, 3));

	free(state.rays);

	return 0;
}
