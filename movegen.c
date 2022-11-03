#include "./movegen.h"

void InitDistances(struct MovementArrays *lookup) {
  U8 north, east, south, west;
  for (int i = 0; i < 64; ++i) {
    north = 7 - (i / 8);
    east = 7 - (i % 8);
    south = i / 8;
    west = i % 8;

    lookup->edge_dist[kNorth][i] = north;
    lookup->edge_dist[kEast][i] = east;
    lookup->edge_dist[kSouth][i] = south;
    lookup->edge_dist[kWest][i] = west;

    lookup->edge_dist[kNorthEast][i] = min(north, east);
    lookup->edge_dist[kSouthEast][i] = min(south, east);
    lookup->edge_dist[kSouthWest][i] = min(south, west);
    lookup->edge_dist[kNorthWest][i] = min(north, west);
  }
}

void InitWhitePawnMovement(struct MovementArrays *lookup) {
  for (int i = 0; i < 64; ++i) {
    lookup->white_pawns[i] = 0;
    if (i / 8 == 0 || i / 8 == 7) {
      continue;
    } else if (i / 8 == 1) {
      lookup->white_pawns[i] += (1ull << (i + kOffsetN + kOffsetN));
    }

    if (lookup->edge_dist[kNorthWest][i]) {
      lookup->white_pawns[i] += 1ull << (i + kOffsetNW);
    }
    if (lookup->edge_dist[kNorthEast][i]) {
      lookup->white_pawns[i] += 1ull << (i + kOffsetNE);
    }
    lookup->white_pawns[i] += 1ull << (i + kOffsetN);
  }
}

void InitBlackPawnMovement(struct MovementArrays *lookup) {
  for (int i = 0; i < 64; ++i) {
    lookup->black_pawns[i] = 0;
    if (i / 8 == 0 || i / 8 == 7) {
      continue;
    } else if (i / 8 == 6) {
      lookup->black_pawns[i] += (1ull << (i + kOffsetS + kOffsetS));
    }

    if (lookup->edge_dist[kNorthWest][i]) {
      lookup->black_pawns[i] += 1ull << (i + kOffsetSW);
    }
    if (lookup->edge_dist[kNorthEast][i]) {
      lookup->black_pawns[i] += 1ull << (i + kOffsetSE);
    }
    lookup->black_pawns[i] += 1ull << (i + kOffsetS);
  }
}

void InitMovementArrays(struct MovementArrays *lookup) {
  InitDistances(lookup);
  InitWhitePawnMovement(lookup);
  InitBlackPawnMovement(lookup);
}
