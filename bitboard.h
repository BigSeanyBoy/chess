/* 
 * DESCRIPTION:
 *      Bitboards use a 64-bit usigned integer to represent the state of
 * 	pieces on a chess board. Because bits may only be 1 or 0, we use
 * 	multiple bitboards to represent the board as a whole: white pieces,
 * 	black pieces, pawns, knights, bishops, rooks, queens, and kings.
 * 	The intersection of these boards gives us any information we may
 * 	need regarding the placement of pieces on the board.
 */
#ifndef BITBOARD_H_
#define BITBOARD_H_

#include "types.h"

/* rank constants */
static const U64 rank1 = 0xFF;
static const U64 rank2 = rank1 << 8;
static const U64 rank3 = rank1 << 16;
static const U64 rank4 = rank1 << 24;
static const U64 rank5 = rank1 << 32;
static const U64 rank6 = rank1 << 40;
static const U64 rank7 = rank1 << 48;
static const U64 rank8 = rank1 << 56;

/* file constants */
static const U64 afile = 0x101010101010101;
static const U64 bfile = afile << 1;
static const U64 cfile = afile << 2;
static const U64 dfile = afile << 3;
static const U64 efile = afile << 4;
static const U64 ffile = afile << 5;
static const U64 gfile = afile << 6;
static const U64 hfile = afile << 7;

U64 push(U64 pawns, U64 empty, enum color side);
U64 dblpush(U64 pawns, U64 empty, enum color side);
U64 pattack(U64 pawns, U64 enemybb, enum color side);

U64 pmoves(U64 pawns, U64 enemybb, U64 empty, enum color side);

#endif /* BITBOARD_H_ */
