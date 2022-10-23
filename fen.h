#ifndef FEN
#define FEN

#include "board.h"

void empty_bb(struct CBoard *position);
void fenstr_placement(struct CBoard *position, char *fenstr);
void fenstr_castling(struct CBoard *position, char *fenstr);
void fenstr_enpassasnt(struct CBoard *position, char *fenstr);
U32 fenstr_moves(struct CBoard *position, char *fenstr);
void import_fenstr(struct CBoard *position, char *fenstr);

#endif