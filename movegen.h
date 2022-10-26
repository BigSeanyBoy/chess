#ifndef MOVEGEN
#define MOVEGEN

#include "board.h"

U64 w_single_push_targets(U64 pawns, U64 empty);
U64 w_double_push_targets(U64 pawns, U64 empty);
U64 b_single_push_targets(U64 pawns, U64 empty);
U64 b_double_push_targets(U64 pawns, U64 empty);

U64 w_pawn_attack_east(U64 pawns);
U64 w_pawn_attack_west(U64 pawns);
U64 b_pawn_attack_east(U64 pawns);
U64 b_pawn_attack_west(U64 pawns);

U64 w_pawn_capture_east(U64 pawns, U64 bpieces);
U64 w_pawn_capture_west(U64 pawns, U64 bpieces);
U64 b_pawn_capture_east(U64 pawns, U64 wpieces);
U64 b_pawn_capture_west(U64 pawns, U64 wpieces);

#endif