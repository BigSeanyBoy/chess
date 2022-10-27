#include "./position.h"

U64 North(U64 bitboard) {
  return bitboard << NORTH;
}

U64 NorthEast(U64 bitboard) {
  return bitboard << NORTH_EAST;
}

U64 SouthEast(U64 bitboard) {
  return bitboard << SOUTH_EAST;
}

U64 South(U64 bitboard) {
  return bitboard << SOUTH;
}

U64 SouthWest(U64 bitboard) {
  return bitboard << SOUTH_WEST;
}

U64 NorthWest(U64 bitboard) {
  return bitboard << NORTH_WEST;
}
