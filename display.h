#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdio.h>

#include "./position.h"

#define DEFAULT "\x1b[0m"
#define RED "\x1b[91m"
#define BLUE "\x1b[94m"

void DisplayPiece(struct CBoard *position, U64 bit);
void DisplaySquare(struct CBoard *position, U64 bit);
void BlackDisplay(struct CBoard *position);
void WhiteDisplay(struct CBoard *position);
void Display(struct CBoard *position, enum Color side);

#endif  // DISPLAY_H_
