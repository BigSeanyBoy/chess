#include "./display.h"

void SquareDisplay(U8 piece) {
  if (piece == 0) {
    printf("x ");
    return;
  }

  (piece & kWhite) ? printf("%s", DEFAULT) : printf("%s", RED);

  switch (piece & 7) {
    case kPawn:
      printf("p");
      break;
    case kKnight:
      printf("N");
      break;
    case kBishop:
      printf("B");
      break;
    case kRook:
      printf("R");
      break;
    case kQueen:
      printf("Q");
      break;
    case kKing:
      printf("K");
      break;
  }

  printf("%s ", DEFAULT);
}

void BlackDisplay(struct CBoard *position) {
  printf("\n      h g f e d c b a\n\n");
  for (int rank = 0; rank < 8; ++rank) {
    printf("   %d  ", rank + 1);
    for (int file = 7; file >= 0; --file) {
      SquareDisplay(position->pieces[rank * 8 + file]);
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
      SquareDisplay(position->pieces[rank * 8 + file]);
    }
    printf(" %d\n", rank + 1);
  }
  printf("\n      a b c d e f g h\n\n");
}

void Display(struct CBoard *position, enum Color side) {
  printf("\033[1;0H");
  side == kWhite ? WhiteDisplay(position) : BlackDisplay(position);
}
