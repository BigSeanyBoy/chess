#ifndef TESTS_UNIT_H_
#define TESTS_UNIT_H_

#include <assert.h>
#include <stdio.h>

#include "../position.h"

#define DEFAULT "\x1b[0m"
#define GREEN "\x1b[32m"

void TestFENEmpty();
void TestFENStart();
void TestFENFirstMove();
void TestFENMidGame();

void TestFEN();

void TestingSuite();

#endif  // TESTS_UNIT_H_
