/* 
 * DESCRIPTION:
 *      Target calculation tests for pattern generation of the various
 *      pieces. Tests check pattern and attack calculations for each piece
 *      type to ensure accurate move generation.
 */
#ifndef TARGETS_H_
#define TARGETS_H_

#include <assert.h>
#include <stdio.h>

#include "../types.h"
#include "../bitboard.h"

#define DEFAULT "\x1b[0m"
#define GREEN "\x1b[032m"

void pawntargets();

void testdriver();

#endif /* TARGETS_H_ */
