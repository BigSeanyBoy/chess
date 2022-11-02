#include "./movegen.h"

void InitDistances(struct MovementArrays *lookup) {
  U8 north, east, south, west;
  for (int i = 0; i < 64; ++i) {
    north = 7 - (i / 8);
    east = 7 - (i % 8);
    south = i / 8;
    west = i % 8;

    lookup->distance_from_edge[kNorth][i] = north;
    lookup->distance_from_edge[kEast][i] = east;
    lookup->distance_from_edge[kSouth][i] = south;
    lookup->distance_from_edge[kWest][i] = west;

    lookup->distance_from_edge[kNorthEast][i] = min(north, east);
    lookup->distance_from_edge[kSouthEast][i] = min(south, east);
    lookup->distance_from_edge[kSouthWest][i] = min(south, west);
    lookup->distance_from_edge[kNorthWest][i] = min(north, west);
  }
}
