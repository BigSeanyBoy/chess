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

/*
 * Pawn Promotion
 *
 * DESCRIPTION:
 *      Generate all possible pawn promotions.
 */
void pawnpromo(U16 move, U16 *movelist, int *count) {
        assert(move != 0);
        for (U16 piece = N_KNIGHT - 3; piece < N_QUEEN - 3; ++piece) {
                movelist[*count] = move | (piece << 12);
                ++(*count);
        }
}

/*
 * Generate Pawn Moves
 *
 * DESCRIPTION:
 *      Generate all pawn moves in a given position. This includes pushes,
 *      captures, en passant, and promotions.
 */
void genpawns(struct position *state, U16 *movelist, int *count) {
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

        if (pawns == 0) { return; }

        assert(pawns == (state->boards[N_PAWN] & ~enemies));
        assert((pawns & enemies) == 0);
        assert((empty & pawns & enemies) == 0);

        enum square ept = state->eptarget;
        if (ept != NULL_SQ) {
                assert((ept >= A1) && (ept <= H8));
                U64 eptbb = 1ull << ept;
                if (side == WHITE) {
                        if (southwest(eptbb) & pawns) {
                                assert(pawns & (1ull << (ept - 9)));
                                movelist[*count] = ept | (ept - 9);
                                ++(*count);
                        }
                        if (southeast(eptbb) & pawns) {
                                assert(pawns & (1ull << (ept - 7)));
                                movelist[*count] = ept | (ept - 7);
                                ++(*count);
                        }
                } else {
                        if (northwest(eptbb) & pawns) {
                                assert(pawns & (1ull << (ept + 7)));
                                movelist[*count] = ept | (ept + 7);
                                ++(*count);
                        }
                        if (northeast(eptbb) & pawns) {
                                assert(pawns & (1ull << (ept + 9)));
                                movelist[*count] = ept | (ept + 9);
                                ++(*count);
                        }
                }
        }

        while (pawns != 0) {
                int source = bitscanreset(&pawns);
                U64 p = 1ull << source;
                U64 targets = pmoves(p, enemies, empty, side);
                while (targets != 0) {
                        int promo = targets & RANK_1 || targets & RANK_8;
                        int dest = bitscanreset(&targets);
                        U16 move = dest | (source << 6);
                        assert((move & dest) == dest);
                        assert(((move >> 6) & source) == source);
                        //if (!legal(move)) { continue; }
                        if (promo) {
                                pawnpromo(move, movelist, count);
                        } else {
                                movelist[*count] = move;
                                ++(*count);
                        }
                }
        }
}

/*
 * Move Generation
 *
 * DESCRIPTION:
 *      Generate all possible moves in a given position and return the count.
 */
int movegen(struct position *state, U16 *movelist) {
        int count = 0;
        genpawns(state, movelist, &count);
        return count;
}
