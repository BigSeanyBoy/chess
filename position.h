#ifndef POSITION_H_
#define POSITION_H_

#include <stdint.h>

typedef uint8_t U8;

enum Color {
  kWhite = 8,
  kBlack = 16
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
  kA8, kB8, kC8, kD8, kE8, kF8, kG8, kH8
};

struct CBoard {
  U8 pieces[64];
  enum Color side;
};

void ImportFEN(struct CBoard *position, char *fenstr);

#endif  // POSITION_H_
