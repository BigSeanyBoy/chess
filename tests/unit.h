#ifndef TESTS_UNIT_H_
#define TESTS_UNIT_H_

#include <assert.h>
#include <stdio.h>

#include "../position.h"
#include "../movegen.h"
#include "../types.h"

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
