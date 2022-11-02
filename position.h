#ifndef POSITION_H_
#define POSITION_H_

#include "./types.h"

struct CBoard {
  U16 move_list[256];
  U8 pieces[64];
  enum Color side;

  // Record castling rights and en passant target square for each position,
  // but only add them to the move list after checking if the move is
  // available during move generation.
  enum CastlingRights castling_rights;
  enum Square en_passant_target;
  U16 move_number;
  U8 halfmove_clock;
};

void ImportFEN(struct CBoard *position, char *fenstr);

#endif  // POSITION_H_
