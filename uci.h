/*
 * DESCRIPTION:
 *      Compatibility with the Universal Chess Interface, allowing the engine
 *      to communicate with other chess-playing entities.
 * 
 *      This code is based on the UCI implementations in Vice by Bluefever
 *      Software (https://www.youtube.com/@BlueFeverSoft) and Olithink by
 *      Oliver Brausch (https://github.com/olithink/OliThink).
 */
#ifndef UCI_H_
#define UCI_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "movegen.h"
#include "position.h"
#include "search.h"

#define MAXBUF 2500
#define STARTFEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

void id();
void parsemvs(char *line, struct position *state);
void parsepos(char *line, struct position *state);
void parsego(char *line, struct position *state, struct sinfo *info);

void uci();

#endif /* UCI_H_ */
