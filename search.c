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
 * Random Search
 *
 * DESCRIPTION:
 *      Return a random legal move in the given position.
 */
U16 randsearch(struct position *state) {
        U16 movelist[256];
        U16 move;

        int count = gendriver(state, movelist);
        struct position scopy;
        for (;;) {
                copy(state, &scopy);
                move = movelist[rand() % count];
                if (make(move, &scopy)) { break; }
        }

        return move;
}

/*
 * Negamax
 *
 * DESCRIPTION:
 *      Search all possible variations to the specified depth and evaluate the
 *      position at the leaf node, then return the best score for the current
 *      player.
 */
int negamax(struct position *state, struct sinfo *info, int depth) {
        U16 movelist[256];

	if (depth == 0) {
                ++info->nodes;
		return evaluate(state);
	}

        checkstop(info);
        if (info->stop) { return evaluate(state); }

	int count = gendriver(state, movelist);
        if (count == 0) { return -MATED; }
        assert(count > 0);

	struct position scopy;
        int score;
        int max = -(MATED + 1);

	for (int i = 0; i < count; ++i) {
		copy(state, &scopy);
		if (make(movelist[i], &scopy)) {
                        score = -negamax(&scopy, info, depth - 1);
                        if (score > max) {
                                max = score;
                        }
		}
	}
	
	return max;
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

        for (int d = 0; d < info->depth; ++d) {
                checkstop(info);
                if (info->stop) { break; }

                U16 movelist[256];
                int count = gendriver(state, movelist);
                struct position scopy;

                int score;
                int max = -(MATED + 1);

                for (int i = 0; i < count; ++i) {
                        copy(state, &scopy);
                        if (make(movelist[i], &scopy)) {
                                score = -negamax(&scopy, info, d);
                                if (score > max) {
                                        max = score;
                                        if (!info->stop) {
                                                bestmove = movelist[i];
                                        }
                                }
                        }
                }
                /* Search should never be called in checkmate */
                assert(bestmove != 0);

                printf("info depth %d time %llu nodes %llu\n",
                       d + 1, gettimems() - info->tstart, info->nodes);
        }

        printf("bestmove ");
        printmv(bestmove);
        printf("\n");
}
