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
void append(U16 move, U16 *movelist, int *count) {
        movelist[*count] = move;
        ++(*count);
}

/*
 * En Passant
 *
 * DESCRIPTION:
 *      Add any possible en passant captures by allied pawns to the move list.
 *      This function should only be called with a valid en passant target
 *      square.
 */
void enpassant(struct position *state, U16 *movelist, int *count) {
        enum square ept = state->eptarget;
        assert((ept >= A1) && (ept <= H8));

        U64 pawns = state->boards[PAWN];
        U64 eptbb = 1ull << ept;
        U16 move = ept | EN_PASSANT;
        int source;

        switch (state->side) {
        case WHITE:
                pawns &= state->boards[WHITE];
                if (southeast(eptbb) & pawns) {
                        source = ept - 7;
                        assert(pawns & (1ull << source));
                        move |= (source << 6);
                        append(move, movelist, count);
                }
                if (southwest(eptbb) & pawns) {
                        source = ept - 9;
                        assert(pawns & (1ull << source));
                        move |= (source << 6);
                        append(move, movelist, count);
                }
                break;
        case BLACK:
                pawns &= state->boards[BLACK];
                if (northwest(eptbb) & pawns) {
                        source = ept + 9;
                        assert(pawns & (1ull << source));
                        move |= (source << 6);
                        append(move, movelist, count);
                }
                if (northeast(eptbb) & pawns) {
                        source = ept + 7;
                        assert(pawns & (1ull << source));
                        move |= (source << 6);
                        append(move, movelist, count);
                }
                break;
        }
}

/*
 * Castling
 *
 * DESCRIPTION:
 *      Add any possible castles to the move list.
 */
void castling(struct position *state, U16 *movelist, int *count) {
        enum castling rights = state->rights;
        U64 occupied = state->boards[OCCUPIED];
        U64 empty = state->boards[EMPTY];

        switch (state->side) {
        case WHITE:
                if (rights & WHITE_OO && (occupied & WHITE_OO_GAP) == 0) {
                        assert((empty & WHITE_OO_GAP) == 0x60ull);
                        U16 move = E1 | (G1 << 6) | CASTLING;
                        append(move, movelist, count);
                }
                if (rights & WHITE_OOO && (occupied & WHITE_OOO_GAP) == 0) {
                        assert((empty & WHITE_OOO_GAP) == 0xeull);
                        U16 move = E1 | (C1 << 6) | CASTLING;
                        append(move, movelist, count);
                }
                break;
        case BLACK:
                if (rights & BLACK_OO && (occupied & BLACK_OO_GAP) == 0) {
                        assert((empty & BLACK_OO_GAP) == (0x60ull << 56));
                        U16 move = E8 | (G8 << 6) | CASTLING;
                        append(move, movelist, count);
                }
                if (rights & BLACK_OOO && (occupied & BLACK_OOO_GAP) == 0) {
                        assert((empty & BLACK_OOO_GAP) == (0xeull << 56));
                        U16 move = E8 | (C8 << 6) | CASTLING;
                        append(move, movelist, count);
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
void pawngen(struct position *state, U16 *movelist, int *count) {
        U64 pawns = state->boards[PAWN];
        switch (state->side) {
        case WHITE:
                pawns &= state->boards[WHITE];
                break;
        case BLACK:
                pawns &= state->boards[BLACK];
                break;
        }

        if (pawns == 0) { return; }

        while (pawns != 0) {
                int source = bitscanreset(&pawns);
                U64 targets = ptargets(source, state);
                U16 promo = targets & (RANK_1 | RANK_8) ? PROMOTION : 0;
                while (targets != 0) {
                        int dest = bitscanreset(&targets);
                        U16 move = dest | (source << 6) | promo;
                        assert((move & dest) == dest);
                        assert(((move >> 6) & source) == source);
                        append(move, movelist, count);
                        if (promo) {
                                append(move | (1 << 12), movelist, count);
                                append(move | (2 << 12), movelist, count);
                                append(move | (3 << 12), movelist, count);
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
            struct position *state,
            U16 *movelist,
            int *count) {
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
                        append(move, movelist, count);
                }
        }
}

int gendriver(struct position *state, U16 *movelist) {
        int count = 0;

        if (state->eptarget != NULL_SQ) {
                enpassant(state, movelist, &count);
        }
        if (state->rights != NO_CASTLING && !incheck(state)) {
                castling(state, movelist, &count);
        }
        pawngen(state, movelist, &count);
        movegen(KNIGHT, &ntargets, state, movelist, &count);
        movegen(BISHOP, &btargets, state, movelist, &count);
        movegen(ROOK, &rtargets, state, movelist, &count);
        movegen(QUEEN, &qtargets, state, movelist, &count);
        movegen(KING, &ktargets, state, movelist, &count);

        return count;
}
