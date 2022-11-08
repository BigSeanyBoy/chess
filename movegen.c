#include "movegen.h"

/*
 * Bitscan with Reset
 *
 * DESCRIPTION:
 *      Get the index of the first set bit then remove that bit from the
 *      board. This function should not be used with the position bitboards
 *      themselves, but rather a copy of those boards.
 */
U64 bitscanreset(U64 *bb) {
        assert(*bb != 0);
        U64 sq = 1ull << __builtin_ctzll(*bb);
        *bb &= *bb - 1;
        assert((*bb & sq) == 0);
        return sq;
}

int movegen(struct position *state, U16 *moves) {
        U64 allies;
        U64 enemies;
        if (state->side == WHITE) {
                allies = state->boards[N_WHITE];
                enemies = state->boards[N_BLACK];
        } else {
                allies = state->boards[N_BLACK];
                enemies = state->boards[N_WHITE];
        }
        U64 occupied = state->boards[N_OCCUPIED];
        U64 empty = state->boards[N_EMPTY];

        U64 movebb;
        int count = 0;

        U64 pawncopy = allies & state->boards[N_PAWN];
        while (pawncopy != 0) {
                U64 pawn = bitscanreset(&pawncopy);
                movebb = pmoves(pawn, enemies, empty, state->side);
        }
}
