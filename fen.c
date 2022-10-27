#include "./fen.h"

void EmptyBB(struct CBoard *position) {
  position->bitboards[N_WHITE] = 0;
  position->bitboards[N_BLACK] = 0;
  position->bitboards[N_PAWN] = 0;
  position->bitboards[N_KNIGHT] = 0;
  position->bitboards[N_BISHOP] = 0;
  position->bitboards[N_ROOK] = 0;
  position->bitboards[N_QUEEN] = 0;
  position->bitboards[N_KING] = 0;
  position->occupied = 0;
}

void FENPlacement(struct CBoard *position, char *fenstr) {
  int bit = 0;

  int rank = 7;
  int file = 0;

  char c;
  while ((c = *fenstr) != ' ') {
    ++fenstr;
    bit = rank * 8 + file;
    if (c >= 'A' && c <= 'Z') {
      position->bitboards[N_WHITE] += (1ull << bit);
      position->occupied += (1ull << bit);
    } else if (c >= 'a' && c <= 'z') {
      position->bitboards[N_BLACK] += (1ull << bit);
      position->occupied += (1ull << bit);
    } else {
      if (c >= '0' && c <= '9') {
        file += (c - '0');
      } else if (c == '/') {
        --rank;
        file = 0;
      }
      continue;
    }

    switch (c) {
      case 'P':
      case 'p':
        position->bitboards[N_PAWN] += (1ull << bit);
        break;
      case 'N':
      case 'n':
        position->bitboards[N_KNIGHT] += (1ull << bit);
        break;
      case 'B':
      case 'b':
        position->bitboards[N_BISHOP] += (1ull << bit);
        break;
      case 'R':
      case 'r':
        position->bitboards[N_ROOK] += (1ull << bit);
        break;
      case 'Q':
      case 'q':
        position->bitboards[N_QUEEN] += (1ull << bit);
        break;
      case 'K':
      case 'k':
        position->bitboards[N_KING] += (1ull << bit);
        break;
    }
    ++file;
  }
  position->empty = ~position->occupied;
  ++fenstr;
}

void FENCastling(struct CBoard *position, char *fenstr) {
  position->castling_rights = 0;
  char c;
  while ((c = *fenstr) != ' ') {
    switch (c) {
      case 'K':
        position->castling_rights += (WHITE_OO);
        break;
      case 'Q':
        position->castling_rights += (WHITE_OOO);
        break;
      case 'k':
        position->castling_rights += (BLACK_OO);
        break;
      case 'q':
        position->castling_rights += (BLACK_OOO);
        break;
    }
    ++fenstr;
  }
  ++fenstr;
}

void FENEnPassant(struct CBoard *position, char *fenstr) {
  char c = *fenstr;
  ++fenstr;
  if (c != '-') {
    // Record en passant target square
    ++fenstr;
  }
  ++fenstr;
}

U32 FENMoves(struct CBoard *position, char *fenstr) {
  char c;
  U32 result;
  while (*fenstr != ' ' && *fenstr != '\0') {
    c = *fenstr;
    result = (result * 10) + (c - '0');
    ++fenstr;
  }
  return result;
}

void ImportFEN(struct CBoard *position, char *fenstr) {
  for (int i = 0; i < 6; ++i) {
    switch (i) {
      case 0:
        EmptyBB(position);
        FENPlacement(position, fenstr);
        break;
      case 1:
        position->side = *fenstr == 'w' ? WHITE : BLACK;
        fenstr += 2;
        break;
      case 2:
        FENCastling(position, fenstr);
        break;
      case 3:
        FENEnPassant(position, fenstr);
        break;
      case 4:
        position->halfmove_clock = FENMoves(position, fenstr);
        break;
      case 5:
        position->nbmoves = FENMoves(position, fenstr);
        break;
    }
  }
}
