#include "./fen.h"

void EmptyBB(struct CBoard *position) {
  position->bitboards[kWhiteBB] = 0;
  position->bitboards[kBlackBB] = 0;
  position->bitboards[kPawnBB] = 0;
  position->bitboards[kKnightBB] = 0;
  position->bitboards[kBishopBB] = 0;
  position->bitboards[kRookBB] = 0;
  position->bitboards[kQueenBB] = 0;
  position->bitboards[kKingBB] = 0;
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
      position->bitboards[kWhiteBB] += (1ull << bit);
      position->occupied += (1ull << bit);
    } else if (c >= 'a' && c <= 'z') {
      position->bitboards[kBlackBB] += (1ull << bit);
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
        position->bitboards[kPawnBB] += (1ull << bit);
        break;
      case 'N':
      case 'n':
        position->bitboards[kKnightBB] += (1ull << bit);
        break;
      case 'B':
      case 'b':
        position->bitboards[kBishopBB] += (1ull << bit);
        break;
      case 'R':
      case 'r':
        position->bitboards[kRookBB] += (1ull << bit);
        break;
      case 'Q':
      case 'q':
        position->bitboards[kQueenBB] += (1ull << bit);
        break;
      case 'K':
      case 'k':
        position->bitboards[kKingBB] += (1ull << bit);
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
        position->castling_rights += (kWhiteOO);
        break;
      case 'Q':
        position->castling_rights += (kWhiteOOO);
        break;
      case 'k':
        position->castling_rights += (kBlackOO);
        break;
      case 'q':
        position->castling_rights += (kBlackOOO);
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
        position->side = *fenstr == 'w' ? kWhite : kBlack;
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
