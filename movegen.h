#ifndef MOVEGEN_H_
#define MOVEGEN_H_

#include "./position.h"

void PawnMoves(struct CBoard *position, U64 *moves, U64 source);
void KnightMoves(struct CBoard *position, U64 *moves, U64 source);
void BishopMoves(struct CBoard *position, U64 *moves, U64 source);
void RookMoves(struct CBoard *position, U64 *moves, U64 source);
void QueenMoves(struct CBoard *position, U64 *moves, U64 source);
void KingMoves(struct CBoard *position, U64 *moves, U64 source);

void MoveGen(struct CBoard *position, U64 *moves);

#endif  // MOVEGEN_H_
