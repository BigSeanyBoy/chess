#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdio.h>

#include "./position.h"

#define DEFAULT "\x1b[0m"
#define RED "\x1b[31m"

void SquareDisplay(U8 piece);
void BlackDisplay(struct CBoard *position);
void WhiteDisplay(struct CBoard *position);
void Display(struct CBoard *position);

#endif  // DISPLAY_H_
