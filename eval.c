#include "eval.h"

/*
 * Material Score
 *
 * DESCRIPTION:
 *      Compute the score based on material difference and piece weight.
 */
int material(struct position *state) {
        U64 allies = state->boards[state->side];
        U64 enemies = state->boards[flip(state->side)];
        assert((allies & enemies) == 0);

        U64 ap = state->boards[PAWN] & allies;
        U64 an = state->boards[KNIGHT] & allies;
        U64 ab = state->boards[BISHOP] & allies;
        U64 ar = state->boards[ROOK] & allies;
        U64 aq = state->boards[QUEEN] & allies;
        U64 ak = state->boards[KING] & allies;

        U64 ep = state->boards[PAWN] & enemies;
        U64 en = state->boards[KNIGHT] & enemies;
        U64 eb = state->boards[BISHOP] & enemies;
        U64 er = state->boards[ROOK] & enemies;
        U64 eq = state->boards[QUEEN] & enemies;
        U64 ek = state->boards[KING] & enemies;

        assert((ap & ep) == 0);
        assert((an & en) == 0);
        assert((ab & eb) == 0);
        assert((ar & er) == 0);
        assert((aq & eq) == 0);
        assert((ak & ek) == 0);

        int matscore = 0;

        matscore += PVAL * (popcount(ap) - popcount(ep));
        matscore += NVAL * (popcount(an) - popcount(en));
        matscore += BVAL * (popcount(ab) - popcount(eb));
        matscore += RVAL * (popcount(ar) - popcount(er));
        matscore += QVAL * (popcount(aq) - popcount(eq));
        matscore += KVAL * (popcount(ak) - popcount(ek));

        return matscore;
}

/*
 * Evaluate
 *
 * DESCRIPTOIN:
 *      Driver for evaluation as a whole. Calls specific evaluation functions
 *      and return the final score.
 */
int evaluate(struct position *state) {
        int score = 0;

        score += material(state);

        return score;
}
