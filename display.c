#include "./display.h"

void DisplayPiece(struct CBoard *position, U64 bit) {
  if (position->bitboards[kPawnBB] & bit) {
          printf("p");
  } else if (position->bitboards[kKnightBB] & bit) {
          printf("N");
  } else if (position->bitboards[kBishopBB] & bit) {
          printf("B");
  } else if (position->bitboards[kRookBB] & bit) {
          printf("R");
  } else if (position->bitboards[kQueenBB] & bit) {
          printf("Q");
  } else if (position->bitboards[kKingBB] & bit) {
          printf("K");
  }
}

void DisplaySquare(struct CBoard *position, U64 bit) {
  if (position->bitboards[kWhiteBB] & bit) {
    printf("%s", BLUE);
    DisplayPiece(position, bit);
  } else if (position->bitboards[kBlackBB] & bit) {
    printf("%s", RED);
    DisplayPiece(position, bit);
  } else {
    printf("x");
  }

  printf("%s ", DEFAULT);
}

void BlackDisplay(struct CBoard *position) {
  printf("\n      h g f e d c b a\n\n");
  for (int rank = 0; rank < 8; ++rank) {
    printf("   %d  ", rank + 1);
    for (int file = 7; file >= 0; --file) {
            DisplaySquare(position, 1ull << (rank * 8 + file));
    }
    printf(" %d\n", rank + 1);
  }
  printf("\n      h g f e d c b a\n\f");
}

void WhiteDisplay(struct CBoard *position) {
  printf("\n      a b c d e f g h\n\n");
  for (int rank = 7; rank >= 0; --rank) {
    printf("   %d  ", rank + 1);
    for (int file = 0; file < 8; ++file) {
            DisplaySquare(position, 1ull << (rank * 8 + file));
    }
    printf(" %d\n", rank + 1);
  }
  printf("\n      a b c d e f g h\n\n");
}

void Display(struct CBoard *position, enum Color side) {
  printf("\033[4;0H");
  side == kWhite ? WhiteDisplay(position) : BlackDisplay(position);
}
