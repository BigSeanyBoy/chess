#ifndef MOVEGEN_H_
#define MOVEGEN_H_

#include <stdint.h>

typedef uint8_t U8;

enum Direction {
  kNorth,
  kEast,
  kSouth,
  kWest,

  kNorthEast,
  kSouthEast,
  kSouthWest,
  kNorthWest
};

struct MovementArrays {
  U8 distance_from_edge[8][64];
};

void InitDistances(struct MovementArrays *lookup);

#endif  // MOVEGEN_H_
