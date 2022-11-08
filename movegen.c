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
        assert(*bb != 0);
        int idx = __builtin_ctzll(*bb);
        *bb &= *bb - 1;
        assert((*bb & (1ull << idx)) == 0);
        return idx;
}

void pawnpromo(U16 move, U16 *movelist, int *count) {
        for (U16 piece = N_KNIGHT - 3; piece < N_QUEEN - 3; ++piece) {
                movelist[*count] = move | (piece << 12);
                ++(*count);
        }
}

void genpawn(struct position *state, U16 *movelist, int *count) {
        enum color side = state->side;
        U64 pawns = state->boards[N_PAWN];
        U64 enemies;
        if (side == WHITE) {
                pawns &= state->boards[N_WHITE];
                enemies = state->boards[N_BLACK];
        } else {
                pawns &= state->boards[N_BLACK];
                enemies = state->boards[N_WHITE];
        }
        U64 empty = state->boards[N_EMPTY];

        while (pawns != 0) {
                int source = bitscanreset(&pawns);
                U64 p = 1ull << source;
                U64 targets = pmoves(p, enemies, empty, side);
                while (targets != 0) {
                        int dest = bitscanreset(&targets);
                        U16 move = dest | (source << 6);
                        if (targets & RANK_1 || targets & RANK_8) {
                                pawnpromo(move, movelist, count);
                        }
                }
        }
}

int movegen(struct position *state, U16 *movelist) {
        return 0;
}
