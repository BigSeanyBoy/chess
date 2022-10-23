#ifndef BOARD
#define BOARD

#include <stdint.h>

typedef uint8_t  U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;

enum piece {
        N_WHITE,
        N_BLACK,
        N_PAWN,
        N_KNIGHT,
        N_BISHOP,
        N_ROOK,
        N_QUEEN,
        N_KING
};

enum color {
        WHITE,
        BLACK
};

enum castle_bit {
        WKS,
        WQS,
        BKS,
        BQS
};

struct CBoard {
        U64 bitboards[8];
        U32 nbmoves;
        U32 halfmove_clock;
        enum color side;
        U8 castling_rights;
};

#endif