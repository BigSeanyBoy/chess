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

void pawnpromo(U16 move, U16 *movelist, int *count);
void genpawn(struct position *state, U16 *movelist, int *count);

int movegen(struct position *state, U16 *movelist);

#endif /* MOVEGEN_H_ */
