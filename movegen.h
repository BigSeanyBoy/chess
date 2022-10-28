#ifndef MOVEGEN_H_
#define MOVEGEN_H_

#include "./position.h"

void MoveGen(struct CBoard *position, U64 *moves);

U64 PawnMoves(struct CBoard *position, U64 *moves, U64 source);
U64 KnightMoves(struct CBoard *position, U64 *moves, U64 source);
U64 BishopMoves(struct CBoard *position, U64 *moves, U64 source);
U64 RookMoves(struct CBoard *position, U64 *moves, U64 source);
U64 QueenMoves(struct CBoard *position, U64 *moves, U64 source);
U64 KingMoves(struct CBoard *position, U64 *moves, U64 source);

U64 WhiteSinglePushTarget(U64 pawn, U64 empty);
U64 WhiteDoublePushTarget(U64 pawn, U64 empty);
U64 BlackSinglePushTarget(U64 pawn, U64 empty);
U64 BlackDoublePushTarget(U64 pawn, U64 empty);

U64 WhitePawnCaptureEast(U64 pawn, U64 enemies);
U64 WhitePawnCaptureWest(U64 pawn, U64 enemies);
U64 BlackPawnCaptureEast(U64 pawn, U64 enemies);
U64 BlackPawnCaptureWest(U64 pawn, U64 enemies);

#endif  // MOVEGEN_H_
