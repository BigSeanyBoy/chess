#ifndef MOVEGEN_H_
#define MOVEGEN_H_

#include "./position.h"

void MoveGen(struct CBoard *position, U64 *moves);

void PawnMoves(struct CBoard *position, U64 *moves, U64 source);
void KnightMoves(struct CBoard *position, U64 *moves, U64 source);
void BishopMoves(struct CBoard *position, U64 *moves, U64 source);
void RookMoves(struct CBoard *position, U64 *moves, U64 source);
void QueenMoves(struct CBoard *position, U64 *moves, U64 source);
void KingMoves(struct CBoard *position, U64 *moves, U64 source);

#endif  // MOVEGEN_H_
