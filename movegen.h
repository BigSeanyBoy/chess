#ifndef MOVEGEN
#define MOVEGEN

#include "board.h"

U64 w_single_push_targets(U64 pawns, U64 empty);
U64 w_double_push_targets(U64 pawns, U64 empty);
U64 b_single_push_targets(U64 pawns, U64 empty);
U64 b_double_push_targets(U64 pawns, U64 empty);

U64 w_pawn_east_attacks(U64 pawns);
U64 w_pawn_west_attacks(U64 pawns);
U64 b_pawn_east_attacks(U64 pawns);
U64 b_pawn_west_attacks(U64 pawns);

#endif