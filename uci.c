#include "uci.h"

/*
 * Engine ID
 *
 * DESCRIPTION:
 *      Identifies the engine to the requesting entity.
 */
void id() {
        printf("id name Omni-Gnome 1.0\n");
        printf("id author Sean Hammell\n");
        /* send any options */
        printf("uciok\n");
}

/*
 * Parse Moves
 *
 * DESCRIPTION:
 *      Parse and make moves specified when the position is set.
 */
void parsemvs(char *line, struct position *state) {
        int r, f, source, dest;
        U16 move;

        while (*line == ' ') { ++line; }
        while (*line != '\n') {
                f = *line - 'a';
                r = *(line + 1) - '1';
                source = 8 * r + f;

                f = *(line + 2) - 'a';
                r = *(line + 3) - '1';
                dest = 8 * r + f;

                line += 4;
                move = dest | (source << 6);

                if (*line != ' ' && *line != '\n') {
                        char promo[] = "nbrq";
                        for (int i = 0; i < 4; ++i) {
                                if (*line == promo[i]) {
                                        move |= (i << 12) | PROMOTION;
                                        ++line;
                                        break;
                                }
                        }
                }

                if (state->eptarget != NULL_SQ && dest == state->eptarget) {
                        move |= EN_PASSANT;
                }

                if ((state->rights & WHITE_CASTLE && source == E1) ||
                    (state->rights & BLACK_CASTLE && source == E8)) {
                        move |= CASTLING;
                }

                make(move, state);
                while (*line == ' ') { ++line; }
        }
}

/*
 * Parse Position
 *
 * DESCRIPTION:
 *      Set position based on specified FEN.
 */
void parsepos(char *line, struct position *state) {
        line += 9;
        char *cp = line;

        if (!strncmp(cp, "startpos", 8)) { setpos(state, STARTFEN); }
        else if (!strncmp(cp, "fen", 3)) { setpos(state, cp + 4); }
        else { setpos(state, STARTFEN); }

        if ((cp = strstr(cp, "moves"))) { parsemvs(cp + 6, state); }

        printpos(state);
}

/*
 * Parse Go
 *
 * DESCRIPTION:
 *      Begin thinking with the specified constraints.
 */
void parsego(char *line, struct position *state, struct sinfo *info) {
        line += 3;
        char *cp = line;

        clrinfo(info);
        int wturn = state->side == WHITE;

        int time = -1;
        int inc = 0;
        int depth = -1;
        int movestogo = 30;
        int movetime = -1;

        if ((cp = strstr(line, "wtime")) && wturn) { time = atoi(cp + 6); }
        if ((cp = strstr(line, "btime")) && !wturn) { time = atoi(cp + 6); }
        if ((cp = strstr(line, "winc")) && wturn) { inc = atoi(cp + 5); }
        if ((cp = strstr(line, "binc")) && !wturn) { inc = atoi(cp + 5); }
        if ((cp = strstr(line, "movestogo"))) { movestogo = atoi(cp + 10); }
        if ((cp = strstr(line, "depth"))) { depth = atoi(cp + 6); }
        if ((cp = strstr(line, "movetime"))) { movetime = atoi(cp + 9); }

        if (movetime != -1) {
                time = movetime;
                movestogo = 1;
        }

        info->tstart = gettimems();
        info->depth = depth;

        if (time != -1) {
                info->tset = 1;
                time /= movestogo;
                time -= 50;
                info->tstop = info->tstart + time + inc;
        }

        if (depth == -1) { info->depth = MAXDEPTH; }

        printf("time: %d, start: %llu, stop: %llu, depth: %d, timeset: %d\n",
               time, info->tstart, info->tstop, info->depth, info->tset);

        if (!strncmp(line, "perft", 5)) {
                perft(state, info, info->depth);
                printf("\nnodes searched: %llu\n", info->nodes);
        } else {
                search(state, info);
        }
}

/*
 * UCI Loop
 *
 * DESCRIPTION:
 *      Listens for UCI commands and responds accordingly. Unknown commands
 *      are ignored.
 */
void uci() {
        printf("Omni-Gnome 1.0\n");
        char line[MAXBUF];

        struct position state;
        struct sinfo info;

        initpos(&state);
        srand(time(NULL));

        for (;;) {
                memset(&line, 0, MAXBUF);
                fflush(stdout);
                clrinfo(&info);

                if (!fgets(line, MAXBUF, stdin)) { continue; }
                if (line[0] == '\n') { continue; }

                if (!strncmp(line, "isready", 7)) { printf("readyok\n"); }
                else if (!strncmp(line, "position", 8)) { parsepos(line, &state); }
                else if (!strncmp(line, "ucinewgame", 10)) { parsepos(STARTFEN, &state); }
                else if (!strncmp(line, "go", 2)) { parsego(line, &state, &info); }
                else if (!strncmp(line, "quit", 4)) { info.quit = 1; }
                else if (!strncmp(line, "uci", 3)) { id(); }

                if (info.quit) { break; }
        }

        freepos(&state);
}