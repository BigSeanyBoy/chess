#ifndef MOVEGEN_H_
#define MOVEGEN_H_

#include "./position.h"

U64 WhiteSinglePushTargets(U64 pawns, U64 empty);
U64 WhiteDoublePushTargets(U64 pawns, U64 empty);
U64 BlackSinglePushTargets(U64 pawns, U64 empty);
U64 BlackDoublePushTargets(U64 pawns, U64 empty);

U64 WhitePawnAttackEast(U64 pawns);
U64 WhitePawnAttackWest(U64 pawns);
U64 BlackPawnAttackEast(U64 pawns);
U64 BlackPawnAttackWest(U64 pawns);

U64 WhitePawnCaptureEast(U64 pawns, U64 black_pieces);
U64 WhitePawnCaptureWest(U64 pawns, U64 black_pieces);
U64 BlackPawnCaptureEast(U64 pawns, U64 white_pieces);
U64 BlackPawnCaptureWest(U64 pawns, U64 white_pieces);

#endif  // MOVEGEN_H_
