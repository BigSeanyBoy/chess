#include "bitboard.h"

/* 
 * Calculate pawn single push targets.
 */
U64 push(U64 pawns, U64 empty, enum color side) {
        U64 shift = side == WHITE ? north(pawns) : south(pawns);
        return shift & empty;
}

/* 
 * Calculate pawn double push targets.
 */
U64 dblpush(U64 pawns, U64 empty, enum color side) {
        U64 dblshift = push(pawns, empty, side);
        dblshift = push(dblshift, empty, side);
        return side == WHITE ? (dblshift & rank4) : (dblshift & rank5);
}

/* 
 * Calculate pawn attack targets.
 */
U64 pattack(U64 pawns, U64 enemybb, enum color side) {
        U64 targets = 0;
        if (side == WHITE) {
                targets |= northeast(pawns) & enemybb & (~afile);
                targets |= northwest(pawns) & enemybb & (~hfile);
        } else {

                targets |= southeast(pawns) & enemybb & (~afile);
                targets |= southwest(pawns) & enemybb & (~hfile);
        }
        return targets;
}

/*
 * Calculate all pawn targets in a given position.
 */
U64 pmoves(U64 pawns, U64 enemybb, U64 empty, enum color side) {
        U64 targets = 0;
        targets |= push(pawns, empty, side);
        targets |= dblpush(pawns, empty, side);
        targets |= pattack(pawns, enemybb, side);
        return targets;
}