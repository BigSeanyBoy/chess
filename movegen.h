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

#endif  // MOVEGEN_H_
