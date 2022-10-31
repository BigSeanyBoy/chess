#include "./position.h"
#include "./display.h"

int main() {
  printf("\033[2J");

  struct CBoard position;
  char *fenstr = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

  ImportFEN(&position, fenstr);

  Display(&position, kWhite);

  return 0;
}
