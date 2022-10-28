#include "./movegen.h"

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
