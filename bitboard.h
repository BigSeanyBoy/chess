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

/* rank constants */
#define RANK_1 0xFFull
#define RANK_2 (RANK_1 << 8)
#define RANK_3 (RANK_1 << 16)
#define RANK_4 (RANK_1 << 24)
#define RANK_5 (RANK_1 << 32)
#define RANK_6 (RANK_1 << 40)
#define RANK_7 (RANK_1 << 48)
#define RANK_8 (RANK_1 << 56)

/* file constants */
#define FILE_A 0x0101010101010101ull
#define FILE_B (FILE_A << 1)
#define FILE_C (FILE_A << 2)
#define FILE_D (FILE_A << 3)
#define FILE_E (FILE_A << 4)
#define FILE_F (FILE_A << 5)
#define FILE_G (FILE_A << 6)
#define FILE_H (FILE_A << 7)

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

#define min(A, B) ((A) < (B) ? (A) : (B))

U64 push(U64 pawns, U64 empty, enum color side);
U64 dblpush(U64 pawns, U64 empty, enum color side);
U64 pattack(U64 pawns, U64 enemies, enum color side);

U64 pmoves(U64 pawns, U64 enemies, U64 empty, enum color side);
U64 nmoves(U64 knights, U64 allies);
U64 kmoves(U64 king, U64 allies);

struct raylookup {
	U64 north[64];
	U64 east[64];
	U64 south[64];
	U64 west[64];

	U64 northeast[64];
	U64 southeast[64];
	U64 southwest[64];
	U64 northwest[64];
};

void edgedist(int edgedist[], int sq);
void initrays(struct raylookup *rays);

U64 bmoves(enum square sq, U64 occupied, U64 enemies, struct raylookup *rays);
U64 rmoves(enum square sq, U64 occupied, U64 enemies, struct raylookup *rays);
U64 qmoves(enum square sq, U64 occupied, U64 enemies, struct raylookup *rays);

#endif /* BITBOARD_H_ */
