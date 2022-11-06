/*
 * DESCRIPTION:
 *	Information and utilities regarding the state of a chess game. The
 *	position holds information such as piece placement, side to move,
 *	castling rights, and so on. The position also determines the legality
 *	of moves and is responsible for making/unmaking moves.
 */
#ifndef POSITION_H_
#define POSITION_H_

#include "types.h"
#include "bitboard.h"

struct position {
	U64 boards[10];
	enum color side;
	enum castling rights;
	enum square eptarget;
	int rule50;
	int plynb;
};

#endif /* POSITION_H_ */
