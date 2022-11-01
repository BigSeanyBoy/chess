#include <string.h>

#include "./position.h"
#include "./display.h"
#include "./tests/unit.h"

int main(int argc, char *argv[]) {
  if (argc == 1) {
    printf("\033[2J");
    struct CBoard position;
    char *fenstr = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    ImportFEN(&position, fenstr);

    Display(&position, kWhite);
  } else if (strcmp(*(++argv), "-test") == 0) {
    TestingSuite();
  }

  return 0;
}
