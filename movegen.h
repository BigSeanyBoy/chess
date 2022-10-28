#ifndef MOVEGEN_H_
#define MOVEGEN_H_

#include "./position.h"

void MoveGen(struct CBoard *position, U64 *moves);

U64 PawnMoves(U64 pawn, U64 enemies, U64 empty);
U64 KnightMoves(U64 knight, U64 enemies, U64 empty);
U64 BishopMoves(U64 bishop, U64 enemies, U64 empty);
U64 RookMoves(U64 rook, U64 enemies, U64 empty);
U64 QueenMoves(U64 queen, U64 enemies, U64 empty);
U64 KingMoves(U64 king, U64 enemies, U64 empty);

U64 WhiteSinglePushTargets(U64 pawn, U64 empty);
U64 WhiteDoublePushTargets(U64 pawn, U64 empty);
U64 BlackSinglePushTargets(U64 pawn, U64 empty);
U64 BlackDoublePushTargets(U64 pawn, U64 empty);

U64 WhitePawnCapturesEast(U64 pawn, U64 enemies);
U64 WhitePawnCapturesWest(U64 pawn, U64 enemies);
U64 BlackPawnCapturesEast(U64 pawn, U64 enemies);
U64 BlackPawnCapturesWest(U64 pawn, U64 enemies);

#endif  // MOVEGEN_H_
