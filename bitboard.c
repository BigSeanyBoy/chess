#include "bitboard.h"

/* 
 * Pawn Single Push
 * 
 * DESCRIPTION:
 *      Calculate pawn single push targets.
 */
U64 push(U64 pawns, U64 empty, enum color side) {
        U64 shift;
        if (side == WHITE) {
                shift = north(pawns) & empty;
                assert(shift == ((pawns << 8) & empty));
                assert((shift & RANK_2) == 0);
        } else {
                shift = south(pawns) & empty;
                assert(shift == ((pawns >> 8) & empty));
                assert((shift & RANK_7) == 0);
        }
        return shift;
}

/* 
 * Pawn Double Push
 *
 * DESCRIPTION:
 *      Calculate pawn double push targets.
 */
U64 dblpush(U64 pawns, U64 empty, enum color side) {
        U64 dblshift = push(pawns, empty, side);
        dblshift = push(dblshift, empty, side);
        if (side == WHITE) {
                dblshift &= RANK_4;
                assert((dblshift & (~RANK_4)) == 0);
        } else {
                dblshift &= RANK_5;
                assert((dblshift & (~RANK_5)) == 0);
        }
        return dblshift;
}

/* 
 * Pawn Attack
 *
 * DESCRIPTION:
 *      Calculate pawn attack targets.
 */
U64 pattack(U64 pawns, U64 enemies, enum color side) {
        U64 targets = 0;
        if (side == WHITE) {
                targets |= northeast(pawns) & enemies;
                assert((targets & ((~enemies) | FILE_A)) == 0);
                targets |= northwest(pawns) & enemies;
                assert((targets & ((~enemies) | FILE_H)) == 0);
        } else {
                targets |= southeast(pawns) & enemies;
                assert((targets & ((~enemies) | FILE_A)) == 0);
                targets |= southwest(pawns) & enemies;
                assert((targets & ((~enemies) | FILE_H)) == 0);
        }
        return targets;
}

/*
 * Pawn Moves
 *
 * DESCRIPTION:
 *      Calculate all pawn targets in a given position.
 */
U64 pmoves(U64 pawns, U64 enemies, U64 empty, enum color side) {
        U64 targets = 0;
        targets |= push(pawns, empty, side);
        targets |= dblpush(pawns, empty, side);
        targets |= pattack(pawns, enemies, side);
        return targets;
}

/*
 * Knight Moves
 *
 * DESCRIPTION:
 *      Calculate all knight targets in a given position. 
 */
U64 nmoves(U64 knights, U64 allies) {
        U64 targets = 0;
        U64 eshift = east(knights);
        U64 wshift = west(knights);
        targets |= ((eshift | wshift) << 16) & (~allies);
        assert(targets == ((knights << 15 | knights << 17) & (~allies)));
        targets |= ((eshift | wshift) >> 16) & (~allies);
        assert(targets == ((knights >> 15 | knights >> 17) & (~allies)));
        U64 eshift = east(eshift);
        U64 wshift = west(wshift);
        targets |= ((eshift | wshift) << 8) & (~allies);
        assert(targets == ((knights << 6 | knights << 10) & (~allies)));
        targets |= ((eshift | wshift) >> 8) & (~allies);
        assert(targets == ((knights >> 6 | knights >> 10) & (~allies)));
        assert((targets & allies) == 0);
        return targets;
}
