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

void TestDistanceFromEdge();
void TestPawnMovement();
void TestKnightMovement();
void TestBishopMovement();
void TestRookMovement();
void TestQueenMovement();
void TestKingMovement();

void TestFEN();
void TestMovement();

void TestingSuite();

#endif  // TESTS_UNIT_H_
