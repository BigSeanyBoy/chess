/*
 * DESCRIPTION:
 *      Generation of all possible moves in a given position. By serializing
 *      the bitboards and generating moves for the current side, we are able
 *      to populate a list with every legal move.
 */
#ifndef MOVEGEN_H_
#define MOVEGEN_H_

#include "types.h"
#include "bitboard.h"
#include "position.h"

int bitscanreset(U64 *bb);

#endif /* MOVEGEN_H_ */
