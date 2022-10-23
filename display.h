#ifndef DISPLAY
#define DISPLAY

#include <stdio.h>

#include "board.h"

#define DEFAULT "\x1b[0m"
#define RED "\x1b[91m"
#define BLUE "\x1b[94m"

void display_piece(struct CBoard *position, U64 bit);
void display_square(struct CBoard *position, U64 bit);
void black_display(struct CBoard *position);
void white_display(struct CBoard *position);
void display(struct CBoard *position, enum color side);

#endif