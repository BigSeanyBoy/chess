/*
 * DESCRIPTION:
 *      Construction and traversal of search trees in order to find possible
 *      game states that may be evaluated to select a move from the current
 *      position.
 */
#ifndef SEARCH_H_
#define SEARCH_H_

#include "stdio.h"
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#include "types.h"
#include "position.h"
#include "movegen.h"
#include "eval.h"

#define MAXDEPTH 20
#define NEGINF (MATE * 2)
#define INF    (-MATE * 2)

U64 gettimems();

void clrinfo(struct sinfo *info);

int inputwaiting();
void readinput(struct sinfo *info);

void checkstop(struct sinfo *info);

U64 perft(struct position *state, struct sinfo *info, int depth);

int quiesce(struct position *state, struct sinfo *info, int depth,
            int alpha, int beta, U16 move);
int alphabeta(struct position *state, struct sinfo *info, int depth,
              int alpha, int beta);

void search(struct position *state, struct sinfo *info);

#endif /* SEARCH_H_ */
