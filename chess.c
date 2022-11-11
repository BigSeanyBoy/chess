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
	printf("%d\n", gendriver(&state, movelist));

	free(state.rays);

	return 0;
}
