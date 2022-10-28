#include "./movegen.h"

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

  U64 source;
  for (int shift = 0; shift < 63; ++shift) {
    source = 1ull << shift;

    if (position->occupied & source) {
      if (position->bitboards[kPawnBB] & source) {
        PawnMoves(position, moves, source);
      } else if (position->bitboards[kKnightBB] & source) {
        KnightMoves(position, moves, source);
      } else if (position->bitboards[kBishopBB] & source) {
        BishopMoves(position, moves, source);
      } else if (position->bitboards[kRookBB] & source) {
        RookMoves(position, moves, source);
      } else if (position->bitboards[kQueenBB] & source) {
        QueenMoves(position, moves, source);
      } else if (position->bitboards[kKingBB] & source) {
        KingMoves(position, moves, source);
      }
    }
  }
}

U64 PawnMoves(struct CBoard *position, U64 *moves, U64 source) {
  U64 targets = 0;

  switch (position->side) {
    case kWhite:
      targets |= (North(source)) & position->empty;
      targets |= (North(North(source))) & position->empty & kRank4;
      targets |= (NorthEast(source)) & position->bitboards[kBlackBB];
      targets |= (NorthWest(source)) & position->bitboards[kBlackBB];
    case kBlack:
      targets |= (South(source)) & position->empty;
      targets |= (South(South(source))) & position->empty & kRank5;
      targets |= (SouthEast(source)) & position->bitboards[kWhiteBB];
      targets |= (SouthWest(source)) & position->bitboards[kWhiteBB];
  }

  return targets;
}

U64 KnightMoves(struct CBoard *position, U64 *moves, U64 source) {
  return 0ull;
}

U64 BishopMoves(struct CBoard *position, U64 *moves, U64 source) {
  return 0ull;
}

U64 RookMoves(struct CBoard *position, U64 *moves, U64 source) {
  return 0ull;
}

U64 QueenMoves(struct CBoard *position, U64 *moves, U64 source) {
  return 0ull;
}

U64 KingMoves(struct CBoard *position, U64 *moves, U64 source) {
  return 0ull;
}
