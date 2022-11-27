/*
 * DESCRIPTION:
 *      Evaluation heuristics for a board position. There are many possible
 *      factors that go into evaluation and many combinations of those factors
 *      which make up a complete heuristic. The evaluation below will start
 *      minimalistic and lightweight to grow overtime as deemed nevessary.
 */
#ifndef EVAL_H_
#define EVAL_H_

#include <assert.h>

#include "types.h"
#include "position.h"
#include "bitboard.h"
#include "movegen.h"

#define popcount(x) __builtin_popcountll(x)

#define MATE -30000
#define DRAW 0

enum values {
        PVAL = 100,
        NVAL = 300,
        BVAL = 320,
        RVAL = 500,
        QVAL = 900,
};

int pawns(struct position *state, U64 ap, U64 ep);
int evaluate(struct position *state);

#endif /* EVAL_H_ */
