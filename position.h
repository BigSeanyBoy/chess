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
#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "bitboard.h"

#define abs(A) ((A) < 0 ? (-A) : (A))
#define mid(A, B) (((A) + (B)) / 2)
#define isupper(C) (((C) >= 'A' && (C) <= 'Z') ? 1 : 0)

void edgedist(int edgedist[], int sq);
void initrays(struct raylookup *rays);
void initpos(struct position *state);
void freepos(struct position *state);

void putpiece(struct position *state, char c, int sq, U64 sqbb);
void setpos(struct position *state, char *fenstr);
void printmv(U16 move);
void printpos(struct position *state);

void updatecastle(struct position *state, enum square sq);
void makeep(enum square dest, struct position *state);
void makecastle(enum square dest, struct position *state);
int make(U16 move, struct position *state);

int incheck(struct position *state, enum square checksq);

void copy(struct position *state, struct position *copy);

#endif /* POSITION_H_ */
