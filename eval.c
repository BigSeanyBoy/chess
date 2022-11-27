#include "eval.h"

/*
 * Evaluate
 *
 * DESCRIPTOIN:
 *      Evaluates the position based on material and mobility. Mobility is
 *      calculated as the number of pseudo-legal moves for each side. If either
 *      side is in check, we do not factor mobility into the score.
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

        struct position scopy;
        copy(state, &scopy);
        scopy.side = flip(scopy.side);
        scopy.eptarget = NULL_SQ;

        if (incheck(state, NULL_SQ)) { return score -= 50; }
        if (incheck(&scopy, NULL_SQ)) { return score += 50; }

        U16 movelist[256];
        int mobility = 0;

        mobility += gendriver(state, movelist);
        mobility -= gendriver(&scopy, movelist);

        mobility *= 10;
        
        score += mobility;

        return score;
}
