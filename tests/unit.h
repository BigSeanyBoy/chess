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

void TestDistanceFromEdge(struct MovementArrays *lookup);
void TestWhitePawnMovement(struct MovementArrays *lookup);
void TestBlackPawnMovement(struct MovementArrays *lookup);
void TestKnightMovement(struct MovementArrays *lookup);
void TestBishopMovement(struct MovementArrays *lookup);
void TestRookMovement(struct MovementArrays *lookup);
void TestQueenMovement(struct MovementArrays *lookup);
void TestKingMovement(struct MovementArrays *lookup);

void TestFEN();
void TestMovement();

void TestingSuite();

#endif  // TESTS_UNIT_H_
