#include "./position.h"

U64 North(U64 bitboard) { return bitboard << kNorth; }

U64 NorthEast(U64 bitboard) { return bitboard << kNorthEast; }

U64 East(U64 bitboard) { return bitboard << kEast; }

U64 SouthEast(U64 bitboard) { return bitboard << kSouthEast; }

U64 South(U64 bitboard) { return bitboard << kSouth; }

U64 SouthWest(U64 bitboard) { return bitboard << kSouthWest; }

U64 West(U64 bitboard) { return bitboard << kWest; }

U64 NorthWest(U64 bitboard) { return bitboard << kNorthWest; }
