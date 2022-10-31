#include "./position.h"

void ImportFEN(struct CBoard *position, char *fenstr) {
  for (int i = 0; i < 63; ++i) { position->pieces[i] = 0; }

  int rank = 7;
  int file = 0;
  while (*fenstr != ' ') {
    if (*fenstr == '/') {
      --rank;
      file = 0;
    } else if (*fenstr >= '0' && *fenstr <= '9') {
      file += *fenstr - '0';
    } else {
      U8 piece = (*fenstr >= 'A' && *fenstr <= 'Z') ? kWhite : kBlack;
      switch (*fenstr) {
          case 'p':
          case 'P':
            piece += kPawn;
            break;
          case 'n':
          case 'N':
            piece += kKnight;
            break;
          case 'b':
          case 'B':
            piece += kBishop;
            break;
          case 'r':
          case 'R':
            piece += kRook;
            break;
          case 'q':
          case 'Q':
            piece += kQueen;
            break;
          case 'k':
          case 'K':
            piece += kKing;
            break;
        }
      position->pieces[8 * rank + file] = piece;
      ++file;
    }
    ++fenstr;
  }

  position->side = *(++fenstr) == 'w' ? kWhite : kBlack;
}
