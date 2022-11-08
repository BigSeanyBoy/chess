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
void append(U16 move, U16 *movelist, int *count);

void pawnpromo(U16 move, U16 *movelist, int *count);
void enpassant(struct position *state, int *count);

void genpawns(struct position *state, int *count);
void genknights(struct position *state, int *count);
void genbishops(struct position *state, int *count);
void genrooks(struct position *state, int *count);
void genqueens(struct position *state, int *count);
void genkings(struct position *state, int *count);

int movegen(struct position *state);

#endif /* MOVEGEN_H_ */
