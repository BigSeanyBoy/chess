/*
 * DESCRIPTION:
 *      Generation of all possible moves in a given position. By serializing
 *      the bitboards and generating moves for the current side, we are able
 *      to populate a list with every legal move.
 */
#ifndef MOVEGEN_H_
#define MOVEGEN_H_

#include <assert.h>

#include "types.h"
#include "bitboard.h"
#include "position.h"

int bitscanreset(U64 *bb);
void append(U16 move, struct movelist *moves);

void enpassant(struct position *state);
void castling(struct position *state);
void pawngen(struct position *state);
void movegen(enum piece ptype,
            U64 (*targets)(enum square, struct position *),
            struct position *state);


void gendriver(struct position *state);

#endif /* MOVEGEN_H_ */
