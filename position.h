/*
 * DESCRIPTION:
 *	Information and utilities regarding the state of a chess game. The
 *	position holds information such as piece placement, side to move,
 *	castling rights, and so on. The position also determines the legality
 *	of moves and is responsible for making/unmaking moves.
 */
#ifndef POSITION_H_
#define POSITION_H_

#include <assert.h>

#include "types.h"
#include "bitboard.h"

#define isupper(C) (((C) >= 'A' && (C) <= 'Z') ? 1 : 0)

struct position {
	struct raylookup rays;
	U64 boards[10];
	enum color side;
	enum castling rights;
	enum square eptarget;
	int rule50;
	int plynb;
};

void putpiece(struct position *state, char c, U64 sq);

void setpos(struct position *state, char *fenstr);

int legal(U16 move);

#endif /* POSITION_H_ */
