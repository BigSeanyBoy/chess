#ifndef MOVEGEN_H_
#define MOVEGEN_H_

#include "./types.h"

struct MovementArrays {
  U8 distance_from_edge[8][64];
};

void InitDistances(struct MovementArrays *lookup);

#endif  // MOVEGEN_H_
