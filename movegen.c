#include "movegen.h"

U64 white_single_push(U64 pawns, U64 empty)
{
        return shift_north(pawns) & empty;
}

U64 white_double_push(U64 pawns, U64 empty)
{
        const U64 rank4 = 0x00000000FF000000ull;
        U64 single_push = white_single_push(pawns, empty);
        return shift_north(single_push) & empty & RANK4;
}

U64 black_single_push(U64 pawns, U64 empty)
{
        return shift_south(pawns) & empty;
}

U64 black_double_push(U64 pawns, U64 empty)
{
        U64 single_push = black_single_push(pawns, empty);
        return shift_south(single_push) & empty & RANK5;
}