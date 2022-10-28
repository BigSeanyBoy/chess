#ifndef POSITION_H_
#define POSITION_H_

#include <stdint.h>

typedef uint8_t  U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;

enum File {
  kFileA = 0x0101010101010101,
  kFileB = kFileA << 1,
  kFileC = kFileA << 2,
  kFileD = kFileA << 3,
  kFileE = kFileA << 4,
  kFileF = kFileA << 5,
  kFileG = kFileA << 6,
  kFileH = kFileA << 7
};

enum Rank {
  kRank1 = 0xFF,
  kRank2 = kRank1 << (8 * 1),
  kRank3 = kRank1 << (8 * 2),
  kRank4 = kRank1 << (8 * 3),
  kRank5 = kRank1 << (8 * 4),
  kRank6 = kRank1 << (8 * 5),
  kRank7 = kRank1 << (8 * 6),
  kRank8 = kRank1 << (8 * 7)
};

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

static inline U64 North(U64 bitboard) { return bitboard << 8; }
static inline U64 NorthEast(U64 bitboard) { return bitboard << 9; }
static inline U64 East(U64 bitboard) { return bitboard << 1; }
static inline U64 SouthEast(U64 bitboard) { return bitboard >> 7; }
static inline U64 South(U64 bitboard) { return bitboard >> 8; }
static inline U64 SouthWest(U64 bitboard) { return bitboard >> 9; }
static inline U64 West(U64 bitboard) { return bitboard >> 1; }
static inline U64 NorthWest(U64 bitboard) { return bitboard << 7; }

#endif  // POSITION_H_
