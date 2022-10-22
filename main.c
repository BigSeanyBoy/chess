#include <stdio.h>

#include "board.h"

#define DEFAULT "\x1b[0m"
#define RED "\x1b[91m"
#define BLUE "\x1b[94m"

void display_piece(struct CBoard *position, U64 bit)
{      
        if (position->bitboards[N_PAWN] & bit) {
                printf("p");
        } else if (position->bitboards[N_KNIGHT] & bit) {
                printf("N");
        } else if (position->bitboards[N_BISHOP] & bit) {
                printf("B");
        } else if (position->bitboards[N_ROOK] & bit) {
                printf("R");
        } else if (position->bitboards[N_QUEEN] & bit) {
                printf("Q");
        } else if (position->bitboards[N_KING] & bit) {
                printf("K");
        }
}

void display_board_white(struct CBoard *position)
{
        printf("\n\n   a b c d e f g h   \n\n");
        for (int i = 0; i < 64; ++i) {
                if (i % 8 == 0) {
                        printf("%d  ", 8 - (i / 8));
                }

                if (position->bitboards[N_WHITE] & (1ull << i)) {
                        printf("%s", BLUE);
                        display_piece(position, 1ull << i);
                }
                else if (position->bitboards[N_BLACK] & (1ull << i)) {
                        printf("%s", RED);
                        display_piece(position, 1ull << i);
                }
                else {
                        printf("x");
                }

                printf("%s ", DEFAULT);

                if ((i + 1) % 8 == 0) {
                        printf(" %d\n", 8 - (i / 8));
                }
        }
        printf("\n   a b c d e f g h   \n\n");
}

int main() 
{
        struct CBoard position;
        char *fenstr = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1\0";
        import_fenstr(&position, fenstr);

        char engine;
        printf("Are you playing for the engine? [y/n]: ");
        engine = getchar();
        while ((getchar()) != '\n');

        enum color side;
        printf("Which color would you like to play as? [w/b]: ");
        side = getchar() == 'w' ? WHITE : BLACK;
        while ((getchar()) != '\n');

        display_board_white(&position);

        return 0;
}