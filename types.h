/* 
 * DESCRIPTION:
 *      Useful types and definitions for manipulating the state of a
 *      board and gathering information on a position.
 */
#ifndef TYPES_H_
#define TYPES_H_

#include <stdint.h>

typedef uint64_t U64;

enum color {
        WHITE,
        BLACK
};

/* cardinal bitboard shifts */
static inline U64 north(U64 bb) { return bb << 8; }
static inline U64 east(U64 bb) { return bb << 1; }
static inline U64 south(U64 bb) { return bb >> 8; }
static inline U64 west(U64 bb) { return bb >> 1; }

/* ordinal bitboard shifts */
static inline U64 northeast(U64 bb) { return bb << 9; }
static inline U64 southeast(U64 bb) { return bb >> 7; }
static inline U64 southwest(U64 bb) { return bb >> 9; }
static inline U64 northwest(U64 bb) { return bb << 7; }

#endif /* TYPES_H_ */