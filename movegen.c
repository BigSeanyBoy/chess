#include "./movegen.h"

U64 RankMask(int source) {
  return kRank1 << (source & 56);
}

U64 FileMask(int source) {
  return kFileA << (source & 7);
}

U64 MainDiagMask(int source) {
  int diag = 8 * (source & 7) - (source & 56);
  int north = -diag & (diag >> 31);
  int south = diag & (-diag >> 31);
  return (kMainDiagonal >> south) << north;
}

U64 AntiDiagMask(int source) {
  int diag = 7 - (source & 7) - (source & 56);
  int north = -diag & (diag >> 31);
  int south = diag & (-diag >> 31);
  return (kMainDiagonal >> south) << north;
}

void PawnMoves(struct CBoard *position, U64 *moves, U64 source) {
  U64 targets = 0;

  switch (position->side) {
    case kWhite:
      targets |= North(source) & position->empty;
      targets |= North(North(source)) & position->empty & kRank4;
      targets |= NorthEast(source) & position->bitboards[kBlackBB] & ~kFileA;
      targets |= NorthWest(source) & position->bitboards[kBlackBB] & ~kFileH;
      break;
    case kBlack:
      targets |= South(source) & position->empty;
      targets |= South(South(source)) & position->empty & kRank5;
      targets |= SouthEast(source) & position->bitboards[kWhiteBB] & ~kFileA;
      targets |= SouthWest(source) & position->bitboards[kWhiteBB] & ~kFileH;
      break;
  }

  moves[source] = targets;
}

void KnightMoves(struct CBoard *position, U64 *moves, U64 source) {
  U64 targets = 0;

  targets |= North(NorthEast(source)) & ~kFileA;
  targets |= East(NorthEast(source)) & ~kFileA & ~kFileB;
  targets |= East(SouthEast(source))  & ~kFileA & ~kFileB;
  targets |= South(SouthEast(source)) & ~kFileA;
  targets |= South(SouthWest(source)) & ~kFileH;
  targets |= West(SouthWest(source)) & ~kFileG & ~kFileH;
  targets |= West(NorthWest(source)) & ~kFileG & ~kFileH;
  targets |= North(NorthWest(source)) & ~kFileH;

  switch (position->side) {
    case kWhite:
      targets &= ~(position->bitboards[kWhiteBB]);
      break;
    case kBlack:
      targets &= ~(position->bitboards[kBlackBB]);
      break;
  }

  moves[source] = targets;
}

void BishopMoves(struct CBoard *position, U64 *moves, U64 source) {
  return;
}

void RookMoves(struct CBoard *position, U64 *moves, U64 source) {
  return;
}

void QueenMoves(struct CBoard *position, U64 *moves, U64 source) {
  return;
}

void KingMoves(struct CBoard *position, U64 *moves, U64 source) {
  U64 targets = 0;

  targets |= East(source) | West(source);
  U64 king_set = targets | source;
  targets |= North(king_set) | South(king_set);

  moves[source] = targets;
}

void MoveGen(struct CBoard *position, U64 *moves) {
  U64 enemies;
  switch (position->side) {
    case kWhite:
      enemies = position->bitboards[kBlackBB];
      break;
    case kBlack:
      enemies = position->bitboards[kBlackBB];
      break;
  }

  for (int source = 0; source < 63; ++source) {
    U64 shift = 1ull << source;

    if (position->occupied & source) {
      if (position->bitboards[kPawnBB] & shift) {
        PawnMoves(position, moves, source);
      } else if (position->bitboards[kKnightBB] & shift) {
        KnightMoves(position, moves, source);
      } else if (position->bitboards[kBishopBB] & shift) {
        BishopMoves(position, moves, source);
      } else if (position->bitboards[kRookBB] & shift) {
        RookMoves(position, moves, source);
      } else if (position->bitboards[kQueenBB] & shift) {
        QueenMoves(position, moves, source);
      } else if (position->bitboards[kKingBB] & shift) {
        KingMoves(position, moves, source);
      }
    } else {
      moves[source] = 0;
    }
  }
}
