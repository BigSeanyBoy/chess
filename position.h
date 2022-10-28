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
  kNormal,
  kPromotion = 1 << 14,
  kEnPassant = 2 << 14,
  kCastling = 3 << 14
};

enum Color {
  kWhite,
  kBlack
};

enum CastlingRights {
  kNoCastling,
  kWhiteOO,
  kWhiteOOO = kWhiteOO << 1,
  kBlackOO = kWhiteOO << 2,
  kBlackOOO = kWhiteOO << 3
};

enum Square {
  kA1, kB1, kC1, kD1, kE1, kF1, kG1, kH1,
  kA2, kB2, kC2, kD2, kE2, kF2, kG2, kH2,
  kA3, kB3, kC3, kD3, kE3, kF3, kG3, kH3,
  kA4, kB4, kC4, kD4, kE4, kF4, kG4, kH4,
  kA5, kB5, kC5, kD5, kE5, kF5, kG5, kH5,
  kA6, kB6, kC6, kD6, kE6, kF6, kG6, kH6,
  kA7, kB7, kC7, kD7, kE7, kF7, kG7, kH7,
  kA8, kB8, kC8, kD8, kE8, kF8, kG8, kH8
};

enum Direction {
  kNorth = 8,
  kEast = 1,
  kSouth = -kNorth,
  kWest = -kEast,

  kNorthEast = kNorth + kEast,
  kSouthEast = kSouth + kEast,
  kSouthWest = kSouth + kWest,
  kNorthWest = kNorth + kWest
};

enum Piece {
  kWhiteBB,
  kBlackBB,
  kPawnBB,
  kKnightBB,
  kBishopBB,
  kRookBB,
  kQueenBB,
  kKingBB
};

struct CBoard {
  U64 bitboards[8];
  U64 empty;
  U64 occupied;
  U32 nbmoves;
  U32 halfmove_clock;
  enum Color side;
  U8 castling_rights;
};

#endif  // POSITION_H_
