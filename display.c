#include "display.h"

/*
 * Display the piece type at the given square.
 */
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

/*
 * Determine the color of the piece at the given square and change the output
 * color accordingly or print a default colored "x" if the square is empty. 
 */
void display_square(struct CBoard *position, U64 bit)
{
        if (position->bitboards[N_WHITE] & bit) {
                printf("%s", BLUE);
                display_piece(position, bit);
        }
        else if (position->bitboards[N_BLACK] & bit) {
                printf("%s", RED);
                display_piece(position, bit);
        }
        else {
                printf("x");
        }

        printf("%s ", DEFAULT);   
}

/*
 * Display the board with black pieces at the bottom.
 */
void black_display(struct CBoard *position)
{
        printf("\n      h g f e d c b a\n\n");
        for (int rank = 0; rank < 8; ++rank) {
                printf("   %d  ", rank + 1);
                for (int file = 7; file >= 0; --file) {
                        display_square(position, 1ull << (rank * 8 + file));
                }
                printf(" %d\n", rank + 1);
        }
        printf("\n      h g f e d c b a\n\f");   
}

/*
 * Display the board with white pieces at the bottom.
 */
void white_display(struct CBoard *position)
{
        printf("\n      a b c d e f g h\n\n");
        for (int rank = 7; rank >= 0; --rank) {
                printf("   %d  ", rank + 1);
                for (int file = 0; file < 8; ++file) {
                        display_square(position, 1ull << (rank * 8 + file));
                }
                printf(" %d\n", rank + 1);
        }
        printf("\n      a b c d e f g h\n\n");
}

/*
 * Overwrite the currently displayed board and draw the user's pieces
 * at the bottom.
 */
void display(struct CBoard *position, enum color side)
{
        printf("\033[4;0H");
        side == WHITE ? white_display(position) : black_display(position);
}