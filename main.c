#include <stdio.h>

#include "board.h"

int main() 
{
        struct CBoard position;
        char *fenstr = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
        import_fenstr(&position, fenstr);

        return 0;
}