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

void InitMovementArrays(struct MovementArrays *lookup) {
  InitDistances(lookup);
}
