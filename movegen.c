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
 * Append
 *
 * DESCRIPTION:
 *      Append a move to the move list and increment the count.
 */
void append(U16 move, struct movelist *moves) {
        moves->list[moves->count] = move;
        ++(moves->count);
}

/*
 * Pawn Promotion
 *
 * DESCRIPTION:
 *      Generate all possible pawn promotions.
 */
void pawnpromo(U16 move, struct movelist *moves) {
        assert(move != 0);
        for (U16 piece = KNIGHT - 3; piece < QUEEN - 3; ++piece) {
                move |= (piece << 12);
                append(move, moves);
        }
}

/*
 * En Passant
 *
 * DESCRIPTION:
 *      Add any possible en passant captures by allied pawns to the move list.
 *      This function should only be called with a valid en passant target
 *      square.
 */
void enpassant(struct position *state) {
        enum square ept = state->eptarget;
        assert((ept >= A1) && (ept <= H8));

        U64 pawns = state->boards[PAWN];
        U64 eptbb = 1ull << ept;
        U16 move = ept;
        int source;

        switch (state->side) {
        case WHITE:
                pawns &= state->boards[WHITE];
                if (southeast(eptbb) & pawns) {
                        source = ept - 7;
                        assert(pawns & (1ull << source));
                        move |= (source << 6);
                        append(move, &(state->moves));
                }
                if (southwest(eptbb) & pawns) {
                        source = ept - 9;
                        assert(pawns & (1ull << source));
                        move |= (source << 6);
                        append(move, &(state->moves));
                }
                break;
        case BLACK:
                pawns &= state->boards[BLACK];
                if (northwest(eptbb) & pawns) {
                        source = ept + 9;
                        assert(pawns & (1ull << source));
                        move |= (source << 6);
                        append(move, &(state->moves));
                }
                if (northeast(eptbb) & pawns) {
                        source = ept + 7;
                        assert(pawns & (1ull << source));
                        move |= (source << 6);
                        append(move, &(state->moves));
                }
                break;
        }
}

/*
 * Generate Pawn Moves
 *
 * DESCRIPTION:
 *      Generate all pawn moves in a given position. This includes pushes,
 *      captures, en passant, and promotions.
 */
void pawngen(struct position *state) {
        enum color side = state->side;
        U64 pawns = state->boards[PAWN];
        U64 enemies;
        switch (side) {
        case WHITE:
                pawns &= state->boards[WHITE];
                enemies = state->boards[BLACK];
                break;
        case BLACK:
                pawns &= state->boards[BLACK];
                enemies = state->boards[WHITE];
                break;
        }
        U64 empty = state->boards[EMPTY];

        if (pawns == 0) { return; }

        assert(pawns == (state->boards[PAWN] & ~enemies));
        assert((empty & pawns & enemies) == 0);

        if (state->eptarget != NULL_SQ) {
                /* if legal(move) */
                enpassant(state);
        }

        while (pawns != 0) {
                int source = bitscanreset(&pawns);
                U64 p = 1ull << source;
                U64 targets = ptargets(p, enemies, empty, side);
                while (targets != 0) {
                        int promo = targets & RANK_1 || targets & RANK_8;
                        int dest = bitscanreset(&targets);
                        U16 move = dest | (source << 6);
                        assert((move & dest) == dest);
                        assert(((move >> 6) & source) == source);
                        /* if legal(move) */
                        if (promo) {
                                pawnpromo(move, &(state->moves));
                        } else {
                                append(move, &(state->moves));
                        }
                }
        }
}

/*
 * Move Generation
 *
 * DESCRIPTION:
 *      Generate all possible moves in a given position and return the count.
 *      This function is generalized for all pieces except pawns, taking the
 *      piece type and respective target function for all necessary move
 *      generation.
 */
void movegen(enum piece ptype,
            U64 (*targets)(enum square, struct position *),
            struct position *state) {
        U64 piecebb = state->boards[ptype];
        switch(state->side) {
        case WHITE:
                piecebb &= state->boards[WHITE];
                break;
        case BLACK:
                piecebb &= state->boards[BLACK];
                break;
        }

        if (piecebb == 0) { return; }

        while (piecebb != 0) {
                int source = bitscanreset(&piecebb);
                U64 targetbb = targets(source, state);
                while (targetbb != 0) {
                        int dest = bitscanreset(&targetbb);
                        U16 move = dest | (source << 6);
                        assert((move & dest) == dest);
                        assert(((move >> 6) & source) == source);
                        /* if legal(move) */
                        append(move, &(state->moves));
                }
        }
}

void gendriver(struct position *state) {
        pawngen(state);
        movegen(KNIGHT, &ntargets, state);
        movegen(BISHOP, &btargets, state);
        movegen(ROOK, &rtargets, state);
        movegen(QUEEN, &qtargets, state);
        movegen(KING, &ktargets, state);
}
