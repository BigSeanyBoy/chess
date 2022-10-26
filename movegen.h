#ifndef MOVEGEN
#define MOVEGEN

#include "board.h"

U64 white_single_push(U64 pawns, U64 empty);
U64 white_double_push(U64 pawns, U64 empty);
U64 black_single_push(U64 pawns, U64 empty);
U64 black_double_push(U64 pawns, U64 empty);

#endif