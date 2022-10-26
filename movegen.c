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
        return north(single_push) & empty & RANK4;
}

U64 b_single_push_targets(U64 pawns, U64 empty)
{
        return south(pawns) & empty;
}

U64 b_double_push_targets(U64 pawns, U64 empty)
{
        U64 single_push = b_single_push_targets(pawns, empty);
        return south(single_push) & empty & RANK5;
}

/*
 * Pawn attacks.
 */
U64 w_pawn_east_attacks(U64 pawns)
{
        return north_east(pawns);
}

U64 w_pawn_west_attacks(U64 pawns)
{
        return north_west(pawns);
}

U64 b_pawn_east_attacks(U64 pawns)
{
        return south_east(pawns);
}

U64 b_pawn_west_attacks(U64 pawns)
{
        return south_west(pawns);
}