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
 * Pawn Promotion
 *
 * DESCRIPTION:
 *      Generate all possible pawn promotions.
 */
void pawnpromo(U16 move, U16 *movelist, int *count) {
        assert(move != 0);
        for (U16 piece = KNIGHT - 3; piece < QUEEN - 3; ++piece) {
                move |= (piece << 12);
                append(move, movelist, count);
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
void enpassant(struct position *state, int *count) {
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
                        append(move, state->movelist, count);
                }
                if (southwest(eptbb) & pawns) {
                        source = ept - 9;
                        assert(pawns & (1ull << source));
                        move |= (source << 6);
                        append(move, state->movelist, count);
                }
                break;
        case BLACK:
                pawns &= state->boards[BLACK];
                if (northwest(eptbb) & pawns) {
                        source = ept + 9;
                        assert(pawns & (1ull << source));
                        move |= (source << 6);
                        append(move, state->movelist, count);
                }
                if (northeast(eptbb) & pawns) {
                        source = ept + 7;
                        assert(pawns & (1ull << source));
                        move |= (source << 6);
                        append(move, state->movelist, count);
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
void genpawns(struct position *state, int *count) {
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
                enpassant(state, count);
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
                                pawnpromo(move, state->movelist, count);
                        } else {
                                append(move, state->movelist, count);
                        }
                }
        }
}

/*
 * Generate Knight Moves
 *
 * DESCRIPTION:
 *      Generate all knight moves in a given position.
 */
void genknights(struct position *state, int *count) {
        U64 knights = state->boards[KNIGHT];
        switch(state->side) {
        case WHITE:
                knights &= state->boards[WHITE];
                break;
        case BLACK:
                knights &= state->boards[BLACK];
                break;
        }

        if (knights == 0) { return; }

        /* assert(knights == (state->boards[KNIGHT] & allies)); */

        while (knights != 0) {
                int source = bitscanreset(&knights);
                U64 targets = ntargets(source, state);
                while (targets != 0) {
                        int dest = bitscanreset(&targets);
                        U16 move = dest | (source << 6);
                        assert((move & dest) == dest);
                        assert(((move >> 6) & source) == source);
                        /* if legal(move) */
                        append(move, state->movelist, count);
                }
        }
}

/*
 * Generate Bishop Moves
 *
 * DESCRIPTION:
 *      Generate all bishop moves in a given position.
 */
void genbishops(struct position *state, int *count) {
        U64 bishops = state->boards[BISHOP];
        switch(state->side) {
        case WHITE:
                bishops &= state->boards[WHITE];
                break;
        case BLACK:
                bishops &= state->boards[BLACK];
                break;
        }

        if (bishops == 0) { return; }

        /* assert(bishops == (state->boards[BISHOP] & (~enemies))); */

        while (bishops != 0) {
                int source = bitscanreset(&bishops);
                U64 targets = btargets(source, state);
                while (targets != 0) {
                        int dest = bitscanreset(&targets);
                        U16 move = dest | (source << 6);
                        assert((move & dest) == dest);
                        assert(((move >> 6) & source) == source);
                        /* if legal(move) */
                        append(move, state->movelist, count);
                }
        }
}

/*
 * Generate Rook Moves
 *
 * DESCRIPTION:
 *      Generate all rook moves in a given position.
 */
void genrooks(struct position *state, int *count) {
        U64 rooks = state->boards[ROOK];
        switch(state->side) {
        case WHITE:
                rooks &= state->boards[WHITE];
                break;
        case BLACK:
                rooks &= state->boards[BLACK];
                break;
        }

        if (rooks == 0) { return; }

        /* assert(rooks == (state->boards[ROOK] & (~enemies))); */

        while (rooks != 0) {
                int source = bitscanreset(&rooks);
                U64 targets = rtargets(source, state);
                while (targets != 0) {
                        int dest = bitscanreset(&targets);
                        U16 move = dest | (source << 6);
                        assert((move & dest) == dest);
                        assert(((move >> 6) & source) == source);
                        /* if legal(move) */
                        append(move, state->movelist, count);
                }
        }
}

/*
 * Generate Queen Moves
 *
 * DESCRIPTION:
 *      Generate all queen moves in a given position.
 */
void genqueens(struct position *state, int *count) {
        U64 queens = state->boards[QUEEN];
        switch(state->side) {
        case WHITE:
                queens &= state->boards[WHITE];
                break;
        case BLACK:
                queens &= state->boards[BLACK];
                break;
        }

        if (queens == 0) { return; }

        /* assert(queens == (state->boards[QUEEN] & (~enemies))); */

        while (queens != 0) {
                int source = bitscanreset(&queens);
                U64 targets = qtargets(source, state);
                while (targets != 0) {
                        int dest = bitscanreset(&targets);
                        U16 move = dest | (source << 6);
                        assert((move & dest) == dest);
                        assert(((move >> 6) & source) == source);
                        /* if legal(move) */
                        append(move, state->movelist, count);
                }
        }
}

/*
 * Generate King Moves
 *
 * DESCRIPTION:
 *      Generate all king moves in a given position.
 */
void genking(struct position *state, int *count) {
        U64 king = state->boards[KING];
        switch(state->side) {
        case WHITE:
                king &= state->boards[WHITE];
                break;
        case BLACK:
                king &= state->boards[BLACK];
                break;
        }

        if (king == 0) { return; }

        /* assert(king == (state->boards[KING] & allies)); */

        int source = bitscanreset(&king);
        U64 targets = ktargets(source, state);
        while (targets != 0) {
                int dest = bitscanreset(&targets);
                U16 move = dest | (source << 6);
                assert((move & dest) == dest);
                assert(((move >> 6) & source) == source);
                /* if legal(move) */
                append(move, state->movelist, count);
        }
}

/*
 * Move Generation
 *
 * DESCRIPTION:
 *      Generate all possible moves in a given position and return the count.
 */
int movegen(struct position *state) {
        int count = 0;
        genpawns(state, &count);
        genknights(state, &count);
        genbishops(state, &count);
        genrooks(state, &count);
        genqueens(state, &count);
        genking(state, &count);
        return count;
}
