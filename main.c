#include "./display.h"

int main() {
  printf("\033[2J");

  struct CBoard position;
  
  for (int i = 0; i < 63; ++i) {
    position.pieces[i] = 0;
  }
  position.side = kWhite;

  Display(&position);

  return 0;
}
