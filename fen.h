#ifndef FEN_H_
#define FEN_H_

#include "./position.h"

void EmptyBB(struct CBoard *position);
void FENPlacement(struct CBoard *position, char *fenstr);
void FENCastling(struct CBoard *position, char *fenstr);
void FENEnPassasnt(struct CBoard *position, char *fenstr);
U32 FENMoves(struct CBoard *position, char *fenstr);
void ImportFEN(struct CBoard *position, char *fenstr);

#endif  // FEN_H_
