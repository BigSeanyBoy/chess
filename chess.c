#include "types.h"
#include "bitboard.h"
#include "position.h"
#include "movegen.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
	struct position state;
	char *fenstr = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	setpos(&state, fenstr);

	U16 movelist[256] = {0};
	gendriver(&state, movelist);

	int i = 0;
	while (movelist[i] != 0) {
		++i;
	}
	printf("%d\n", i);

	free(state.rays);

	return 0;
}
