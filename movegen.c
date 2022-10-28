#include "./movegen.h"

void MoveGen(struct CBoard *position, U64 *moves) {
  switch (position->side) {
    case kWhite:
      U64 enemies = position->bitboards[kBlackBB];
      break;
    case kBlack:
      U64 enemies = position->bitboards[kBlackBB];
      break;
  }

  for (U64 source = 1; source < (1ull << 64); source <<= 1) {
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
      targets |= (source << kNorth) & position->empty;
      targets |= (source << kNorth + kNorth) & position->empty & kRank4;
      targets |= (source << kNorthEast) & position->bitboards[kBlackBB];
      targets |= (source << kNorthWest) & position->bitboards[kBlackBB];
    case kBlack:
      targets |= (source << kSouth) & position->empty;
      targets |= (source << kSouth + kSouth) & position->empty & kRank5;
      targets |= (source << kSouthEast) & position->bitboards[kWhiteBB];
      targets |= (source << kSouthWest) & position->bitboards[kWhiteBB];
  }

  return targets;
}
