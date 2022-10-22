#ifndef BOARD
#define BOARD

#include <stdint.h>

typedef uint64_t U64;

struct CBoard {
        U64 wpieces;
        U64 wpawns;
        U64 wknights;
        U64 wbishops;
        U64 wrooks;
        U64 wqueens;
        U64 wking;

        U64 bpieces;
        U64 bpawns;
        U64 bknights;
        U64 bbishops;
        U64 brooks;
        U64 bqueens;
        U64 bking;
}

#endif