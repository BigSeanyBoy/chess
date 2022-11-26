#include "search.h"

/*
 * Get Time in Milliseconds
 *
 * DESCRIPTION:
 *      Get the current time in milliseconds.
 */
U64 gettimems() {
        struct timeval t;
        gettimeofday(&t, NULL);
        return t.tv_sec * 1000ull + t.tv_usec / 1000ull;
}

/*
 * Clear Search Info
 *
 * DESCRIPTION:
 *      Clear previously set search information.
 */
void clrinfo(struct sinfo *info) {
        info->depth = 0;
        info->nodes = 0;

        info->tset = 0;

        info->stop = 0;
        info->quit = 0;
}

/*
 * Input Waiting
 *
 * DESCRIPTION:
 *      Peek at stdin and return whether there is input waiting or not. The
 *      timeout is set to 0 so we are not waiting on the input.
 */
int inputwaiting() {
        fd_set readfds;

        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);

        struct timeval t;
        t.tv_sec = 0;
        t.tv_usec = 0;

        select(16, &readfds, 0, 0, &t);

        return FD_ISSET(STDIN_FILENO, &readfds);
}

/*
 * Read Input
 *
 * DESCRIPTION:
 *      If there is input waiting in stdin, set stop and, if applicable, quit
 *      in the search info.
 */
void readinput(struct sinfo *info) {
        int bytes = -1;
        char input[256];
        char *endc;

        if (inputwaiting()) {
                info->stop = 1;
                while (bytes < 0) {
                        bytes = read(STDIN_FILENO, input, 256);
                }
                endc = strchr(input, '\n');
                if (endc) { *endc = 0; }

                if (strlen(input) > 0) {
                        if (!strncmp(input, "quit", 4)) { info->quit = 1; }
                }
        }
}

/*
 * Check Stop
 *
 * DESCRIPTION:
 *      Check whether time is up or the engine has been told to stop.
 */
void checkstop(struct sinfo *info) {
        if (info->tset && gettimems() > info->tstop) { info->stop = 1; }
        readinput(info);
}

/*
 * Peft
 *
 * DESCRIPTION:
 *      Test move generation by generating all moves to a specified depth and
 *      counting the leaf nodes. If the leaf nodes match a known perft value,
 *      the move generation for that position is correct.
 */
U64 perft(struct position *state, struct sinfo *info, int depth) {
	U16 movelist[256];

	if (depth == 0) {
                info->nodes += 1;
		return 1ull;
	}

        checkstop(info);
        if (info->stop) { return 0ull; }

	int count = gendriver(state, movelist);
	struct position statecopy;
        U64 n;
	U64 nodes = 0;
	for (int i = 0; i < count; ++i) {
		copy(state, &statecopy);
		if (make(movelist[i], &statecopy)) {
                        n = perft(&statecopy, info, depth - 1);
                        if (depth == info->depth) {
                                printmv(movelist[i]);
                                printf(" %llu\n", n);
                        }
                        nodes += n;
		}
	}
	
	return nodes;
}

/*
 * Quiescence Search
 *
 * DESCRIPTION:
 *      Extend the search until a quiet position is reached, then evaluate.
 *      after a 2-ply extension, only evaluate recaptures to avoid search
 *      explosion. Quiescence search allows alpha-beta to stabalize.
 */
int quiesce(struct position *state, struct sinfo *info, int depth,
            int alpha, int beta, U16 move) {
        int standpat = evaluate(state);
        if (standpat >= beta) { return beta; }
        if (standpat < alpha - 975) { return alpha; }
        if (standpat > alpha) { alpha = standpat; }

        checkstop(info);
        if (info->stop) { return evaluate(state); }

        if (state->rule50 == 100) { return DRAW; }

        U16 movelist[256];
	int count = gendriver(state, movelist);
        int legal = 0;

	struct position scopy;
        int score;
        int source;
        int dest;
        int quiet;
        int isep;

	for (int i = 0; i < count; ++i) {
		copy(state, &scopy);
		if (make(movelist[i], &scopy)) {
                        ++info->nodes;
                        ++legal;

                        source = (movelist[i] >> 6) & 63;
                        dest = movelist[i] & 63;

                        quiet = state->piecelist[dest] == NO_PIECE;
                        isep = (movelist[i] & MOVETYPE_MASK) == EN_PASSANT;
                        if (quiet && !isep) { continue; }

                        enum piece agg = state->piecelist[source];
                        enum piece tar = state->piecelist[dest];
                        if (tar - agg < 0) { continue; }

                        int lmdest = move & 63;
                        if (depth < -2 && dest != lmdest) { continue; }

                        score = -quiesce(&scopy, info, depth -1, -beta,
                                         -alpha, movelist[i]);
                        if (score >= beta) { return beta; }
                        if (score > alpha) { alpha = score; }
		}
	}

        if (legal == 0) {
                if (incheck(state, NULL_SQ)) { return MATE; }
                else { return DRAW; }
        }
	
	return alpha;
}

/*
 * Alpha-Beta
 *
 * DESCRIPTION:
 *      Search all possible variations to the specified depth and evaluate the
 *      position at the leaf node. Prune nodes that fall outside of the bounds,
 *      alpha and beta. Internal iterative deepening is used to find the best
 *      move at 1/4 the current depth, allowing for significantly more pruning.
 */
int alphabeta(struct position *state, struct sinfo *info, int depth,
              int alpha, int beta) {
	if (depth == 0) {
		return quiesce(state, info, depth - 1, alpha, beta, 0);
	}

        checkstop(info);
        if (info->stop) { return evaluate(state); }

        if (state->rule50 == 100) { return DRAW; }

        U16 movelist[256];
	int count = gendriver(state, movelist);
        int legal = 0;

	struct position scopy;
        int score;
        
        if (depth > 1) {
                int iid_alpha = alpha;
                for (int i = 0; i < count; ++i) {
                        copy(state, &scopy);
                        if (make(movelist[i], &scopy)) {
                                ++info->nodes;
                                ++legal;
                                score = -alphabeta(&scopy, info, depth / 4, -beta,
                                                   -alpha);
                                if (score > iid_alpha) {
                                        iid_alpha = score;
                                        U16 tmp = movelist[0];
                                        movelist[0] = movelist[i];
                                        movelist[i] = tmp;
                                }
                        }
                }
        }

	for (int i = 0; i < count; ++i) {
		copy(state, &scopy);
		if (make(movelist[i], &scopy)) {
                        ++info->nodes;
                        ++legal;
                        score = -alphabeta(&scopy, info, depth - 1, -beta, 
                                           -alpha);
                        if (score >= beta) { return beta; }
                        if (score > alpha) { alpha = score; }
		}
	}

        if (legal == 0) {
                if (incheck(state, NULL_SQ)) { return MATE - depth; }
                else { return DRAW; }
        }
	
	return alpha;
}

/*
 * Search
 *
 * DESCRIPTION:
 *      Handle search at the top level. Controls iterative deepening and keeps
 *      track of the best move found so far.
 */
void search(struct position *state, struct sinfo *info) {
        U16 bestmove = 0;

        for (int d = 1; d <= info->depth; ++d) {
                U16 movelist[256];
                int count = gendriver(state, movelist);
                struct position scopy;

                int score;
                int alpha = NEGINF;
                int beta = INF;
                U16 prov = 0;

                for (int i = 0; i < count; ++i) {
                        copy(state, &scopy);
                        if (make(movelist[i], &scopy)) {
                                score = -alphabeta(&scopy, info, d - 1, -beta,
                                                   -alpha);
                                if (score > alpha) {
                                        alpha = score;
                                        prov = movelist[i];
                                }
                        }
                }
                /* Search should never be called in checkmate */
                assert(prov != 0);

                checkstop(info);
                if (info->stop) { break; }

                bestmove = prov;
                printf("info pv ");
                printmv(bestmove);
                printf(" depth %d time %llu nodes %llu\n",
                        d, gettimems() - info->tstart, info->nodes);
        }

        printf("bestmove ");
        printmv(bestmove);
        printf("\n");
}
