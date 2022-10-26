#include "board.h"

U64 shift_north(U64 bitboard)
{
        return bitboard << NORTH;
}

U64 shift_south(U64 bitboard)
{
        return bitboard << SOUTH;
}