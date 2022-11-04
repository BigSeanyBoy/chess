#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "types.h"
#include "bitboard.h"

int main(int argc, char *argv[]) {
	if (argc == 1) {
		return 0;
	} else if (strcmp(argv[1], "-test") == 0) {
		U64 wpawns = 0xff00;
		U64 bpawns = 0x2904d20000;
		U64 empty = 0xffffffd6fb2d00ff;

		assert(pmoves(wpawns, bpawns, empty, WHITE) == 0x29ff0000);
		printf("\x1b[032m[PASSED]\x1b[0m white pawn moves\n");
	}
	return 0;
}
