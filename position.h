#ifndef POSITION_H_
#define POSITION_H_

#include <stdint.h>

typedef uint8_t  U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;

const U64 kFileA = 0x0101010101010101;
const U64 kFileB = kFileA << 1;
const U64 kFileC = kFileA << 2;
const U64 kFileD = kFileA << 3;
const U64 kFileE = kFileA << 4;
const U64 kFileF = kFileA << 5;
const U64 kFileG = kFileA << 6;
const U64 kFileH = kFileA << 7;

const U64 kRank1 = 0xFF;
const U64 kRank2 = kRank1 << (8 * 1);
const U64 kRank3 = kRank1 << (8 * 2);
const U64 kRank4 = kRank1 << (8 * 3);
const U64 kRank5 = kRank1 << (8 * 4);
const U64 kRank6 = kRank1 << (8 * 5);
const U64 kRank7 = kRank1 << (8 * 6);
const U64 kRank8 = kRank1 << (8 * 7);

enum MoveType {
  NORMAL,
  PROMOTION = 1 << 14,
  EN_PASSANT = 2 << 14,
  CASTLING = 3 << 14
};

enum Color {
  WHITE,
  BLACK
};

enum CastlingRights {
  NO_CASTLING,
  WHITE_OO,
  WHITE_OOO = WHITE_OO << 1,
  BLACK_OO = WHITE_OO << 2,
  BLACK_OOO = WHITE_OO << 3
};

enum Square {
  A1, B1, C1, D1, E1, F1, G1, H1,
  A2, B2, C2, D2, E2, F2, G2, H2,
  A3, B3, C3, D3, E3, F3, G3, H3,
  A4, B4, C4, D4, E4, F4, G4, H4,
  A5, B5, C5, D5, E5, F5, G5, H5,
  A6, B6, C6, D6, E6, F6, G6, H6,
  A7, B7, C7, D7, E7, F7, G7, H7,
  A8, B8, C8, D8, E8, F8, G8, H8
};

enum Direction {
  NORTH = 8,
  EAST = 1,
  SOUTH = -NORTH,
  WEST = -EAST,

  NORTH_EAST = NORTH + EAST,
  SOUTH_EAST = SOUTH + EAST,
  SOUTH_WEST = SOUTH + WEST,
  NORTH_WEST = NORTH + WEST,
};

enum Piece {
  N_WHITE,
  N_BLACK,
  N_PAWN,
  N_KNIGHT,
  N_BISHOP,
  N_ROOK,
  N_QUEEN,
  N_KING
};

struct CBoard {
  U64 bitboards[8];
  U64 empty;
  U64 occupied;
  U32 nbmoves;
  U32 halfmove_clock;
  U8 side;
  U8 castling_rights;
};

U64 North(U64 bitboard);
U64 NorthEast(U64 bitboard);
U64 SouthEast(U64 bitboard);
U64 South(U64 bitboard);
U64 SouthWest(U64 bitboard);
U64 NorthWest(U64 bitboard);

#endif  // POSITION_H_
