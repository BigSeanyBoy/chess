#include "uci.h"

/*
 * Engine ID
 *
 * DESCRIPTION:
 *      Identifies the engine to the requesting entity.
 */
void id() {
        printf("id name Omni-Gnome\n");
        printf("id author Sean Hammell\n");
        /* send any options */
        printf("uciok\n");
}

/*
 * Parse Position
 *
 * DESCRIPTION:
 *      Set position based on specified FEN.
 */
void parsepos(char *line, struct position *state) {
        line += 9;

        if (!strncmp(line, "startpos", 8)) { setpos(state, STARTFEN); }
        else if (!strncmp(line, "fen", 3)) { setpos(state, line + 4); }
        else { setpos(state, STARTFEN); }

        printpos(state);
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
        initpos(&state);

        for (;;) {
                memset(&line, 0, MAXBUF);
                fflush(stdout);

                if (!fgets(line, MAXBUF, stdin)) { continue; }
                if (line[0] == '\n') { continue; }

                if (!strncmp(line, "uci", 3)) { id(); }
                else if (!strncmp(line, "isready", 7)) { printf("readyok\n"); }
                else if (!strncmp(line, "position", 8)) { parsepos(line, &state); }
                else if (!strncmp(line, "quit", 4)) { break; }
        }

        freepos(&state);
}