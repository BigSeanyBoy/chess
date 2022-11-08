#include "movegen.h"

/*
 * Bitscan with Reset
 *
 * DESCRIPTION:
 *      Get the index of the first set bit then remove that bit from the
 *      board. This function should not be used with the position bitboards
 *      themselves, but rather a copy of those boards.
 */
int bitscanreset(U64 *bb) {
        int idx = __builtin_ctzll(bb);
        *bb &= *bb - 1;
        return idx;
}
