/*
 * DESCRIPTION:
 *	Information and utilities regarding the state of a chess game. The
 *	position holds information such as piece placement, side to move,
 *	castling rights, and so on. The position also responsible for
 *	making/unmaking moves.
 */
#ifndef POSITION_H_
#define POSITION_H_

#include <assert.h>
#include <stdlib.h>

#include "types.h"

#define abs(A) ((A) < 0 ? (-A) : (A))
#define mid(A, B) (((A) + (B)) / 2)
#define isupper(C) (((C) >= 'A' && (C) <= 'Z') ? 1 : 0)
#define flip(S) ((S) == WHITE ? BLACK : WHITE)

struct raylookup {
	U64 north[64];
	U64 east[64];
	U64 south[64];
	U64 west[64];

	U64 northeast[64];
	U64 southeast[64];
	U64 southwest[64];
	U64 northwest[64];
};

void edgedist(int edgedist[], int sq);
void initrays(struct raylookup *rays);

struct position {
	struct raylookup *rays;
	enum piece piecelist[64];
	U64 boards[10];
	enum color side;
	enum castling rights;
	enum square eptarget;
	int rule50;
	int plynb;
};

void putpiece(struct position *state, char c, int sq, U64 sqbb);
void setpos(struct position *state, char *fenstr);

void makeep(enum square dest, struct position *state);
void makecastle(enum square dest, struct position *state);
void make(U16 move, struct position *state);

#endif /* POSITION_H_ */
