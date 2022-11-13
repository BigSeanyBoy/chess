#include "types.h"
#include "bitboard.h"
#include "position.h"
#include "movegen.h"

#include <stdio.h>

U64 perft(struct position *state, int depth) {
	U16 movelist[256];

	if (depth == 0) {
		return incheck(state) ? 0ull : 1ull;
	}

	int count = gendriver(state, movelist);
	struct position statecopy;
	U64 nodes = 0;
	for (int i = 0; i < count; ++i) {
		copy(state, &statecopy);
		make(movelist[i], &statecopy);
		if (incheck(&statecopy)) { continue; }
		nodes += perft(&statecopy, depth - 1);
	}
	
	return nodes;
}

int main(int argc, char *argv[]) {
	struct position state;
	char *fenstr = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";
	setpos(&state, fenstr);

	printf("%llu\n", perft(&state, 2));

	free(state.rays);

	return 0;
}
