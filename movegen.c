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

// Pawn Pushes.
U64 WhiteSinglePushTargets(U64 pawn, U64 empty) {
  return North(pawn) & empty;
}

U64 WhiteDoublePushTargets(U64 pawn, U64 empty) {
  U64 single_push = WhiteSinglePushTargets(pawn, empty);
  return North(single_push) & empty & kRank4;
}

U64 BlackSinglePushTargets(U64 pawn, U64 empty) {
  return South(pawn) & empty;
}

U64 BlackDoublePushTargets(U64 pawn, U64 empty) {
  U64 single_push = BlackSinglePushTargets(pawn, empty);
  return South(single_push) & empty & kRank5;
}

// Pawn Captures.
U64 WhitePawnCapturesEast(U64 pawn, U64 enemies) {
  return NorthEast(pawn) & enemies & ~kFileA;
}

U64 WhitePawnCapturesWest(U64 pawn, U64 enemies) {
  return NorthWest(pawn) & enemies & ~kFileH;
}

U64 BlackPawnCapturesEast(U64 pawn, U64 enemies) {
  return SouthEast(pawn) & enemies & ~kFileA;
}

U64 BlackPawnCapturesWest(U64 pawn, U64 enemies) {
  return SouthWest(pawn) & enemies & ~kFileH;
}
