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

#include <assert.h>

#include "types.h"

/* rank constants */
#define RANK_1 0x00000000000000FF
#define RANK_2 0x000000000000FF00
#define RANK_3 0x0000000000FF0000
#define RANK_4 0x00000000FF000000
#define RANK_5 0x000000FF00000000
#define RANK_6 0x0000FF0000000000
#define RANK_7 0x00FF000000000000
#define RANK_8 0xFF00000000000000

/* file constants */
#define FILE_A 0x0101010101010101
#define FILE_B 0x0202020202020202
#define FILE_C 0x0404040404040404
#define FILE_D 0x0808080808080808
#define FILE_E 0x1010101010101010
#define FILE_F 0x2020202020202020
#define FILE_G 0x4040404040404040
#define FILE_H 0x8080808080808080

U64 push(U64 pawns, U64 empty, enum color side);
U64 dblpush(U64 pawns, U64 empty, enum color side);
U64 pattack(U64 pawns, U64 enemybb, enum color side);

U64 pmoves(U64 pawns, U64 enemybb, U64 empty, enum color side);

#endif /* BITBOARD_H_ */
