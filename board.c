#include "board.h"

U64 north(U64 bitboard)
{
        return bitboard << NORTH;
}

U64 north_east(U64 bitboard)
{
        return bitboard << NORTH_EAST;
}

U64 south_east(U64 bitboard)
{
        return bitboard << SOUTH_EAST;
}

U64 south(U64 bitboard)
{
        return bitboard << SOUTH;
}

U64 south_west(U64 bitboard)
{
        return bitboard << SOUTH_WEST;
}

U64 north_west(U64 bitboard)
{
        return bitboard << NORTH_WEST;
}