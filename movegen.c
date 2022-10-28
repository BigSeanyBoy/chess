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

// Knight Patterns.
U64 KnightsNoNoEa(U64 knights) {
  return (knights << 17) & (~kFileA);
}

U64 KnightsNoEaEa(U64 knights) {
  return (knights << 10) & (~kFileA) & (~kFileB);
}

U64 KnightsSoEaEa(U64 knights) {
  return (knights >> 6) & (~kFileA) & (~kFileB);
}

U64 KnightsSoSoEa(U64 knights) {
  return (knights >> 15) & (~kFileA);
}

U64 KnightsSoSoWe(U64 knights) {
  return (knights >> 17) & (~kFileH);
}

U64 KnightsSoWeWe(U64 knights) {
  return (knights >> 10) & (~kFileH) & (~kFileG);
}

U64 KnightsNoWeWe(U64 knights) {
  return (knights << 6) & (~kFileH) & (~kFileG);
}

U64 KnightsNoNoWe(U64 knights) {
  return (knights << 15) & (~kFileH);
}

// Knight Attacks.
U64 KnightsAttackNoNoEa(U64 knights, U64 empty) {
  return KnightsNoNoEa(knights) & empty;
}

U64 KnightsAttackNoEaEa(U64 knights, U64 empty) {
  return KnightsNoEaEa(knights) & empty;
}

U64 KnightsAttackSoEaEa(U64 knights, U64 empty) {
  return KnightsSoEaEa(knights) & empty;
}

U64 KnightsAttackSoSoEa(U64 knights, U64 empty) {
  return KnightsSoSoEa(knights) & empty;
}

U64 KnightsAttackSoSoWe(U64 knights, U64 empty) {
  return KnightsSoSoWe(knights) & empty;
}

U64 KnightsAttackSoWeWe(U64 knights, U64 empty) {
  return KnightsSoWeWe(knights) & empty;
}

U64 KnightsAttackNoWeWe(U64 knights, U64 empty) {
  return KnightsNoWeWe(knights) & empty;
}

U64 KnightsAttackNoNoWe(U64 knights, U64 empty) {
  return KnightsNoNoWe(knights) & empty;
}

// Knight Captures.
U64 WhiteKnightsCaptureNoNoEa(U64 knights, U64 black_pieces) {
  return KnightsNoNoEa(knights) & black_pieces;
}

U64 WhiteKnightsCaptureNoEaEa(U64 knights, U64 black_pieces) {
  return KnightsNoEaEa(knights) & black_pieces;
}

U64 WhiteKnightsCaptureSoEaEa(U64 knights, U64 black_pieces) {
  return KnightsSoEaEa(knights) & black_pieces;
}

U64 WhiteKnightsCaptureSoSoEa(U64 knights, U64 black_pieces) {
  return KnightsSoSoEa(knights) & black_pieces;
}

U64 WhiteKnightsCaptureSoSoWe(U64 knights, U64 black_pieces) {
  return KnightsSoSoWe(knights) & black_pieces;
}

U64 WhiteKnightsCaptureSoWeWe(U64 knights, U64 black_pieces) {
  return KnightsSoWeWe(knights) & black_pieces;
}

U64 WhiteKnightsCaptureNoWeWe(U64 knights, U64 black_pieces) {
  return KnightsNoWeWe(knights) & black_pieces;
}

U64 WhiteKnightsCaptureNoNoWe(U64 knights, U64 black_pieces) {
  return KnightsNoNoWe(knights) & black_pieces;
}

U64 BlackKnightsCaptureNoNoEa(U64 knights, U64 white_pieces) {
  return KnightsNoNoEa(knights) & white_pieces;
}

U64 BlackKnightsCaptureNoEaEa(U64 knights, U64 white_pieces) {
  return KnightsNoEaEa(knights) & white_pieces;
}

U64 BlackKnightsCaptureSoEaEa(U64 knights, U64 white_pieces) {
  return KnightsSoEaEa(knights) & white_pieces;
}

U64 BlackKnightsCaptureSoSoEa(U64 knights, U64 white_pieces) {
  return KnightsSoSoEa(knights) & white_pieces;
}

U64 BlackKnightsCaptureSoSoWe(U64 knights, U64 white_pieces) {
  return KnightsSoSoWe(knights) & white_pieces;
}

U64 BlackKnightsCaptureSoWeWe(U64 knights, U64 white_pieces) {
  return KnightsSoWeWe(knights) & white_pieces;
}

U64 BlackKnightsCaptureNoWeWe(U64 knights, U64 white_pieces) {
  return KnightsNoWeWe(knights) & white_pieces;
}

U64 BlackKnightsCaptureNoNoWe(U64 knights, U64 white_pieces) {
  return KnightsNoNoWe(knights) & white_pieces;
}
