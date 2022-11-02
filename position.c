#include "./position.h"

void ImportFEN(struct CBoard *position, char *fenstr) {
  for (int i = 0; i < 64; ++i) { position->pieces[i] = 0; }

  U8 rank = 7;
  U8 file = 0;
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
  ++fenstr;

  position->castling_rights = 0;
  while (*(++fenstr) != ' ') {
    switch (*fenstr) {
      case 'K':
        position->castling_rights += kWhiteOO;
        break;
      case 'Q':
        position->castling_rights += kWhiteOOO;
        break;
      case 'k':
        position->castling_rights += kBlackOO;
        break;
      case 'q':
        position->castling_rights += kBlackOOO;
        break;
    }
  }

  if (*(++fenstr) != '-') {
    file = *fenstr - 'a';
    rank = *(++fenstr) - '1';
    U8 square = 8 * rank + file;

    position->en_passant_target = square;
  } else {
    position->en_passant_target = kNullSquare;
  }
  ++fenstr;

  U8 halfmove_clock = 0;
  while (*(++fenstr) != ' ') {
    halfmove_clock = (halfmove_clock * 10) + (*fenstr - '0');
  }
  position->halfmove_clock = halfmove_clock;

  U16 move_number = 0;
  while (*(++fenstr) != '\0') {
    move_number = (move_number * 10) + (*fenstr - '0');
  }
  position->move_number = move_number;
}
