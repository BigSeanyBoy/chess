#ifndef TYPES_H_
#define TYPES_H_

#include <stdint.h>

#define DEFAULT "\x1b[0m"
#define GREEN "\x1b[32m"

#define min(A, B) ((A) < (B) ? (A) : (B))

typedef uint8_t U8;
typedef uint16_t U16;
typedef uint64_t U64;

enum Color {
  kWhite = 8,
  kBlack = 16
};

enum CastlingRights {
  kNoCastling,
  kWhiteOO,
  kWhiteOOO = kWhiteOO << 1,
  kBlackOO = kWhiteOO << 2,
  kBlackOOO = kWhiteOO << 3,

  kWhiteCastling = kWhiteOO | kWhiteOOO,
  kBlackCastling = kBlackOO | kBlackOOO,

  kAnyCastling = kWhiteCastling | kBlackCastling
};

enum Piece {
  kNoPiece,
  kPawn,
  kKnight,
  kBishop,
  kRook,
  kQueen,
  kKing
};

enum Square {
  kA1, kB1, kC1, kD1, kE1, kF1, kG1, kH1,
  kA2, kB2, kC2, kD2, kE2, kF2, kG2, kH2,
  kA3, kB3, kC3, kD3, kE3, kF3, kG3, kH3,
  kA4, kB4, kC4, kD4, kE4, kF4, kG4, kH4,
  kA5, kB5, kC5, kD5, kE5, kF5, kG5, kH5,
  kA6, kB6, kC6, kD6, kE6, kF6, kG6, kH6,
  kA7, kB7, kC7, kD7, kE7, kF7, kG7, kH7,
  kA8, kB8, kC8, kD8, kE8, kF8, kG8, kH8,

  kNullSquare
};

enum Direction {
  kNorth,
  kEast,
  kSouth,
  kWest,

  kNorthEast,
  kSouthEast,
  kSouthWest,
  kNorthWest
};

enum Offset {
  kOffsetN = 8,
  kOffsetE = 1,
  kOffsetS = -kOffsetN,
  kOffsetW = -kOffsetE,

  kOffsetNE = kOffsetN + kOffsetE,
  kOffsetSE = kOffsetS + kOffsetE,
  kOffsetSW = kOffsetS + kOffsetW,
  kOffsetNW = kOffsetN + kOffsetW
};

#endif  // TYPES_H_
