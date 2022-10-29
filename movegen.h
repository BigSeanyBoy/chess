#ifndef MOVEGEN_H_
#define MOVEGEN_H_

#include "./position.h"

void PawnMoves(struct CBoard *position, U64 *moves, U64 source);
void KnightMoves(struct CBoard *position, U64 *moves, U64 source);
void BishopMoves(struct CBoard *position, U64 *moves, U64 source);
void RookMoves(struct CBoard *position, U64 *moves, U64 source);
void QueenMoves(struct CBoard *position, U64 *moves, U64 source);
void KingMoves(struct CBoard *position, U64 *moves, U64 source);

void MoveGen(struct CBoard *position, U64 *moves);

static inline U64 FileMask(int source) {
  return kFileA << (source & 7);
}

static inline U64 MainDiagMask(int source) {
  int diag = 8 * (source & 7) - (source & 56);
  int north = -diag & (diag >> 31);
  int south = diag & (-diag >> 31);
  return (kMainDiagonal >> south) << north;
}

static inline U64 AntiDiagMask(int source) {
  int diag = 7 - (source & 7) - (source & 56);
  int north = -diag & (diag >> 31);
  int south = diag & (-diag >> 31);
  return (kMainDiagonal >> south) << north;
}

static inline U64 NorthMask(int source) {
  return kFileA << source;
}

static inline U64 NorthEastMask(int source) {
  return MainDiagMask(source) & (-2ull << source);
}

static inline U64 EastMask(int source) {
  return 2 * ((1ull << (source | 7)) - (1ull << source));
}

static inline U64 SouthEastMask(int source) {
  return AntiDiagMask(source) & ((1ull << source ) - 1);
}

static inline U64 SouthMask(int source) {
  return kFileH >> (source ^ 63);
}

static inline U64 SouthWestMask(int source) {
  return MainDiagMask(source) & ((1ull << source ) - 1);
}

static inline U64 WestMask(int source) {
  return (1ull << source) - (1ull << (source & 56));
}

static inline U64 NorthWestMask(int source) {
  return AntiDiagMask(source) & (-2ull << source);
}

inline U64 RankMask(int source) {
  return kRank1 << (source & 56);
}


#endif  // MOVEGEN_H_
