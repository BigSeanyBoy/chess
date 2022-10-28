#ifndef MOVEGEN_H_
#define MOVEGEN_H_

#include "./position.h"

U64 WhiteSinglePushTargets(U64 pawns, U64 empty);
U64 WhiteDoublePushTargets(U64 pawns, U64 empty);
U64 BlackSinglePushTargets(U64 pawns, U64 empty);
U64 BlackDoublePushTargets(U64 pawns, U64 empty);

U64 WhitePawnsAttackEast(U64 pawns);
U64 WhitePawnsAttackWest(U64 pawns);
U64 BlackPawnsAttackEast(U64 pawns);
U64 BlackPawnsAttackWest(U64 pawns);

U64 WhitePawnsCaptureEast(U64 pawns, U64 black_pieces);
U64 WhitePawnsCaptureWest(U64 pawns, U64 black_pieces);
U64 BlackPawnsCaptureEast(U64 pawns, U64 white_pieces);
U64 BlackPawnsCaptureWest(U64 pawns, U64 white_pieces);

U64 KnightsNoNoEa(U64 knights);
U64 KnightsNoEaEa(U64 knights);
U64 KnightsSoEaEa(U64 knights);
U64 KnightsSoSoEa(U64 knights);
U64 KnightsSoSoWe(U64 knights);
U64 KnightsSoWeWe(U64 knights);
U64 KnightsNoWeWe(U64 knights);
U64 KnightsNoNoWe(U64 knights);

U64 KnightsAttackNoNoEa(U64 knights, U64 empty);
U64 KnightsAttackNoEaEa(U64 knights, U64 empty);
U64 KnightsAttackSoEaEa(U64 knights, U64 empty);
U64 KnightsAttackSoSoEa(U64 knights, U64 empty);
U64 KnightsAttackSoSoWe(U64 knights, U64 empty);
U64 KnightsAttackSoWeWe(U64 knights, U64 empty);
U64 KnightsAttackNoWeWe(U64 knights, U64 empty);
U64 KnightsAttackNoNoWe(U64 knights, U64 empty);

#endif  // MOVEGEN_H_
