#include "board.h"

void empty_bb(struct CBoard *position)
{
        position->bitboards[N_WHITE] = 0;
        position->bitboards[N_BLACK] = 0;
        position->bitboards[N_PAWN] = 0;
        position->bitboards[N_KNIGHT] = 0;
        position->bitboards[N_BISHOP] = 0;
        position->bitboards[N_ROOK] = 0;
        position->bitboards[N_QUEEN] = 0;
        position->bitboards[N_KING] = 0;
}

void fenstr_placement(struct CBoard *position, char *fenstr)
{
        int bit = 0;
        char c;
        while ((c = *fenstr) != ' ') {
                ++fenstr;
                if (c >= 'A' && c <= 'Z') {
                        position->bitboards[N_WHITE] += 1 << bit;
                } else if (c >= 'a' && c <= 'z') {
                        position->bitboards[N_BLACK] += 1 << bit;
                } else {
                        if (c >= '0' && c <= '9')
                                bit += c - '0';
                        
                        continue;
                }

                switch (c) {
                case 'P':
                case 'p':
                        position->bitboards[N_PAWN] += 1 << bit;
                        break;
                case 'N':
                case 'n':
                        position->bitboards[N_KNIGHT] += 1 << bit;
                        break;
                case 'B':
                case 'b':
                        position->bitboards[N_BISHOP] += 1 << bit;
                        break;
                case 'R':
                case 'r':
                        position->bitboards[N_ROOK] += 1 << bit;
                        break;
                case 'Q':
                case 'q':
                        position->bitboards[N_QUEEN] += 1 << bit;
                        break;
                case 'K':
                case 'k':
                        position->bitboards[N_KING] += 1 << bit;
                        break;
                }
                ++bit;
        }
        ++fenstr;
}

void fenstr_castling(struct CBoard *position, char *fenstr)
{
        position->castling_rights = 0;
        char c;
        while ((c = *fenstr) != ' ') {
                switch (c) {
                case 'K':
                        position->castling_rights += (1 << WKS);
                        break;
                case 'Q':
                        position->castling_rights += (1 << WQS);
                        break;
                case 'k':
                        position->castling_rights += (1 << BKS);
                        break;
                case 'q':
                        position->castling_rights += (1 << BQS);
                        break;
                }
                ++fenstr;
        }
        ++fenstr;
}

void fenstr_enpassant(struct CBoard *position, char *fenstr)
{
        char c = *fenstr;
        ++fenstr;
        if (c != '-') {
                /* Record en passant target square */
                ++fenstr;
        }
        ++fenstr;
}

U32 fenstr_moves(struct CBoard *position, char *fenstr)
{
        char c;
        U32 result;
        while (*fenstr != ' ' || *fenstr != '\0') {
                c = *fenstr;
                result = (result * 10) + (c - '0');
                ++fenstr;
        }
        return result;
}

void import_fenstr(struct CBoard *position, char *fenstr)
{
        for (int i = 0; i < 6; ++i) {
                switch (i) {
                case 0:
                        empty_bb(position);
                        fenstr_placement(position, fenstr);
                        break;
                case 1:
                        position->side = *fenstr == 'w' ? WHITE : BLACK;
                        fenstr += 2;
                        break;
                case 2:
                        fenstr_castling(position, fenstr);
                        break;
                case 3:
                        fenstr_enpassant(position, fenstr);
                        break;
                case 4:
                        position->halfmove_clock = fenstr_moves(position, fenstr);
                        break;
                case 5:
                        position->nbmoves = fenstr_moves(position, fenstr);
                        break;
                }
        }
}