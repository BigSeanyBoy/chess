/* 
 * DESCRIPTION:
 * 	Bitboards use a 64-bit usigned integer to represent the state of
 * 	pieces on a chess board. Because bits may only be 1 or 0, we use
 * 	multiple bitboards to represent the board as a whole: white pieces,
 * 	black pieces, pawns, knights, bishops, rooks, queens, and kings.
 * 	The intersection of these boards gives us any information we may
 * 	need regarding the placement of pieces on the board.
 */
#ifndef BITBOARD_H_
#define BITBOARD_H_

#include <assert.h>

#include "types.h"

/* cardinal bitboard shifts */
#define north(BB) (BB << 8)
#define east(BB) ((BB << 1) & (~FILE_A))
#define south(BB) (BB >> 8)
#define west(BB) ((BB >> 1) & (~FILE_H))

/* ordinal bitboard shifts */
#define northeast(BB) ((BB << 9) & (~FILE_A))
#define southeast(BB) ((BB >> 7) & (~FILE_A))
#define southwest(BB) ((BB >> 9) & (~FILE_H))
#define northwest(BB) ((BB << 7) & (~FILE_H))

U64 push(U64 pawns, U64 empty, enum color side);
U64 dblpush(U64 pawns, U64 empty, enum color side);
U64 pattack(U64 pawns, U64 enemies, enum color side);

U64 ptargets(enum square sq, struct position *state);
U64 ntargets(enum square sq, struct position *state);
U64 btargets(enum square sq, struct position *state);
U64 rtargets(enum square sq, struct position *state);
U64 qtargets(enum square sq, struct position *state);
U64 ktargets(enum square sq, struct position *state);

#endif /* BITBOARD_H_ */
