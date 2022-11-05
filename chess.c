#include <assert.h>
#include <string.h>

#include "types.h"
#include "bitboard.h"

#include "tests/targets.h"

int main(int argc, char *argv[]) {
	if (argc == 1) {
		return 0;
	} else if (strcmp(argv[1], "-test") == 0) {
		testdriver();
	}
	return 0;
}
