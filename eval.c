#include "eval.h"

/*
 * Evaluate
 *
 * DESCRIPTOIN:
 *      Driver for evaluation as a whole. Calls specific evaluation functions
 *      and return the final score.
 */
int evaluate(struct position *state) {
        U64 allies = state->boards[state->side];
        U64 enemies = state->boards[flip(state->side)];
        assert((allies & enemies) == 0);

        U64 ap = state->boards[PAWN] & allies;
        U64 an = state->boards[KNIGHT] & allies;
        U64 ab = state->boards[BISHOP] & allies;
        U64 ar = state->boards[ROOK] & allies;
        U64 aq = state->boards[QUEEN] & allies;

        U64 ep = state->boards[PAWN] & enemies;
        U64 en = state->boards[KNIGHT] & enemies;
        U64 eb = state->boards[BISHOP] & enemies;
        U64 er = state->boards[ROOK] & enemies;
        U64 eq = state->boards[QUEEN] & enemies;

        assert((ap & ep) == 0);
        assert((an & en) == 0);
        assert((ab & eb) == 0);
        assert((ar & er) == 0);
        assert((aq & eq) == 0);

         int score = 0;

        score += PVAL * (popcount(ap) - popcount(ep));
        score += NVAL * (popcount(an) - popcount(en));
        score += BVAL * (popcount(ab) - popcount(eb));
        score += RVAL * (popcount(ar) - popcount(er));
        score += QVAL * (popcount(aq) - popcount(eq));

        U16 movelist[256];
        int count = gendriver(state, movelist);

        struct position scopy;
        int amob = 0;
        for (int i = 0; i < count; ++i) {
                copy(state, &scopy);
                if (make(movelist[i], &scopy)) { ++amob; }
        }

        copy(state, &scopy);
        scopy.side = flip(scopy.side);
        count = gendriver(&scopy, movelist);

        struct position sfcopy;
        int emob = 0;
        for (int i = 0; i < count; ++i) {
                copy(&scopy, &sfcopy);
                if (make(movelist[i], &sfcopy)) { ++emob; }
        }

        score += 10 * (amob - emob);

        score += 50 * incheck(&scopy, NULL_SQ);

        return score;
}
