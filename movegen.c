#include "movegen.h"

/*
 * Pawn pushes.
 */
U64 w_single_push_targets(U64 pawns, U64 empty)
{
        return north(pawns) & empty;
}

U64 w_double_push_targets(U64 pawns, U64 empty)
{
        U64 single_push = w_single_push_targets(pawns, empty);
        return north(single_push) & empty & RANK_4;
}

U64 b_single_push_targets(U64 pawns, U64 empty)
{
        return south(pawns) & empty;
}

U64 b_double_push_targets(U64 pawns, U64 empty)
{
        U64 single_push = b_single_push_targets(pawns, empty);
        return south(single_push) & empty & RANK_5;
}

/*
 * Pawn attacks.
 */
U64 w_pawn_attack_east(U64 pawns)
{
        return north_east(pawns) & (~FILE_A);
}

U64 w_pawn_attack_west(U64 pawns)
{
        return north_west(pawns) & (~FILE_H);
}

U64 b_pawn_attack_east(U64 pawns)
{
        return south_east(pawns) & (~FILE_A);
}

U64 b_pawn_attack_west(U64 pawns)
{
        return south_west(pawns) & (~FILE_H);
}

/*
 * Pawn captures.
 */
U64 w_pawn_capture_east(U64 pawns, U64 bpieces)
{
        return w_pawn_attack_east(pawns) & bpieces;
}

U64 w_pawn_capture_west(U64 pawns, U64 bpieces)
{
        return w_pawn_attack_west(pawns) & bpieces;
}

U64 b_pawn_capture_east(U64 pawns, U64 wpieces)
{
        return b_pawn_attack_east(pawns) & wpieces;
}

U64 b_pawn_capture_west(U64 pawns, U64 wpieces)
{
        return b_pawn_attack_west(pawns) & wpieces;
}