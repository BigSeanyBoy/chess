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

static inline U64 RankMask(int source) {
  return kRank1 << (source & 56);
}

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

#endif  // MOVEGEN_H_
