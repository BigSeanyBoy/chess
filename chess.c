#include "types.h"
#include "bitboard.h"
#include "position.h"
#include "movegen.h"

#include <stdio.h>

void decodemove(U16 move, struct position *state) {
	int source = (move >> 6) & 63;
	int dest = move & 63;

	printf("%c", (source % 8) + 'a');
	printf("%d", (source/ 8) + 1);
	printf("%c", (dest % 8) + 'a');
	printf("%d\t", (dest / 8) + 1);
}

U64 perft(struct position *state, int depth) {
	U16 movelist[256];

	if (depth == 0) {
		return 1ull;
	}

	int count = gendriver(state, movelist);
	struct position statecopy;
	U64 nodes = 0;
	for (int i = 0; i < count; ++i) {
		copy(state, &statecopy);
		make(movelist[i], &statecopy);
		if (!incheck(NULL_SQ, &statecopy)) {
			statecopy.side = flip(statecopy.side);
			int n = perft(&statecopy, depth - 1);
			if (depth == 5) {
				decodemove(movelist[i], state);
				printf("%d\n", n);
			}
			nodes += n;
		}
	}
	
	return nodes;
}

int main(int argc, char *argv[]) {
	struct position state;
	char *fenstr = "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10";
	setpos(&state, fenstr);

	printf("%llu\n", perft(&state, 5));

	free(state.rays);

	return 0;
}
