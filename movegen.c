#include "./movegen.h"

// Pawn Pushes.
U64 WhiteSinglePushTargets(U64 pawns, U64 empty) {
  return north(pawns) & empty;
}

U64 WhiteDoublePushTargets(U64 pawns, U64 empty) {
  U64 single_push = WhiteSinglePushTargets(pawns, empty);
  return North(single_push) & empty & kRank4;
}

U64 BlackSinglePushTargets(U64 pawns, U64 empty) {
  return South(pawns) & empty;
}

U64 BlackDoublePushTargets(U64 pawns, U64 empty) {
  U64 single_push = BlackSinglePushTargets(pawns, empty);
  return South(single_push) & empty & kRank5;
}

// Pawn Attacks.
U64 WhitePawnsAttackEast(U64 pawns) { return NorthEast(pawns) & (~kFileA); }

U64 WhitePawnsAttackWest(U64 pawns) { return NorthWest(pawns) & (~kFileH); }

U64 BlackPawnsAttackEast(U64 pawns) { return SouthEast(pawns) & (~kFileA); }

U64 BlackPawnsAttackWest(U64 pawns) { return SouthWest(pawns) & (~kFileH); }

// Pawn Captures.
U64 WhitePawnsCaptureEast(U64 pawns, U64 black_pieces) {
  return WhitePawnsAttackEast(pawns) & black_pieces;
}

U64 WhitePawnsCaptureWest(U64 pawns, U64 black_pieces) {
  return WhitePawnsAttackWest(pawns) & black_pieces;
}

U64 BlackPawnsCaptureEast(U64 pawns, U64 white_pieces) {
  return BlackPawnsAttackEast(pawns) & white_pieces;
}

U64 BlackPawnsCaptureWest(U64 pawns, U64 white_pieces) {
  return BlackPawnsAttackWest(pawns) & white_pieces;
}

// Knight Attacks.
U64 WhiteKnightsNoNoEa(U64 knights) {
  return (knights << 17) & (~kFileA);
}

U64 WhiteKnightsNoEaEa(U64 knights) {
  return (knights << 10) & (~kFileA) & (~kFileB);
}

U64 WhiteKnightsSoEaEa(U64 knights) {
  return (knights >> 6) & (~kFileA) & (~kFileB);
}

U64 WhiteKnightsSoSoEa(U64 knights) {
  return (knights >> 15) & (~kFileA);
}

U64 WhiteKnightsSoSoWe(U64 knights) {
  return (knights >> 17) & (~kFileH);
}

U64 WhiteKnightsSoWeWe(U64 knights) {
  return (knights >> 10) & (~kFileH) & (~kFileG);
}

U64 WhiteKnightsNoWeWe(U64 knights) {
  return (knights << 6) & (~kFileH) & (~kFileG);
}

U64 WhiteKnightsNoNoWe(U64 knights) {
  return (knights << 15) & (~kFileH);
}
