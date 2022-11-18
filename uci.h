/*
 * DESCRIPTION:
 *      Compatibility with the Universal Chess Interface, allowing the engine
 *      to communicate with other chess-playing entities.
 */
#ifndef UCI_H_
#define UCI_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "position.h"

#define MAXBUF 2500
#define STARTFEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

void id();
void parsepos(char *line, struct position *state);

void uci();

#endif /* UCI_H_ */
