/* 
 * DESCRIPTION:
 *      Useful types and definitions for manipulating the state of a
 *      board and gathering information on a position.
 */
#ifndef TYPES_H_
#define TYPES_H_

#include <stdint.h>

typedef uint16_t U16;
typedef uint64_t U64;

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

/* squares between kings and rooks */
#define WHITE_OO_GAP 0x60ull
#define WHITE_OOO_GAP 0xeull
#define BLACK_OO_GAP WHITE_OO_GAP << 56
#define BLACK_OOO_GAP WHITE_OOO_GAP << 56

/* intersectin with move gives type of move */
#define MOVETYPE_MASK (3ull << 14)

#define min(A, B) ((A) < (B) ? (A) : (B))

enum movetype {
	NORMAL,
	PROMOTION = 1 << 14,
	EN_PASSANT = 2 << 14,
	CASTLING = 3 << 14
};

enum color {
	WHITE,
	BLACK
};

enum castling {
	NO_CASTLING,
	WHITE_OO,
	WHITE_OOO,
	BLACK_OO,
	BLACK_OOO
};

enum piece {
	PAWN = 2,
	KNIGHT,
	BISHOP,
	ROOK,
	QUEEN,
	KING,
	OCCUPIED,
	EMPTY,

	NO_PIECE
};

enum square {
	A1, B1, C1, D1, E1, F1, G1, H1,
	A2, B2, C2, D2, E2, F2, G2, H2,
	A3, B3, C3, D3, E3, F3, G3, H3,
	A4, B4, C4, D4, E4, F4, G4, H4,
	A5, B5, C5, D5, E5, F5, G5, H5,
	A6, B6, C6, D6, E6, F6, G6, H6,
	A7, B7, C7, D7, E7, F7, G7, H7,
	A8, B8, C8, D8, E8, F8, G8, H8,

	NULL_SQ
};

#endif /* TYPES_H_ */
