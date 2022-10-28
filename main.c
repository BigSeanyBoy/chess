#include "./display.h"
#include "./fen.h"

int main() {
  printf("\033[0;0H\033[2J");
  printf("Welcome to the \x1b[34;1mNeptune Chess Engine\x1b[0m!\n");
  struct CBoard position;
  char *fenstr = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  ImportFEN(&position, fenstr);

  enum Color side;
  printf("\nWhich side would you like to play as? [w/b]: ");
  side = getchar() == 'w' ? kWhite : kBlack;
  while ((getchar()) != '\n') {}

  Display(&position, side);

  return 0;
}
