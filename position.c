#include "position.h"

/*
 * Put Piece
 *
 * DESCRIPTION:
 *      Insert the specified piece into the proper bitboards based on the
 *      provided character descriptor and square.
 */
void putpiece(struct position *state, char c, U64 sq) {
        state->boards[isupper(c) ? N_WHITE : N_BLACK] |= sq;
        switch (c) {
        case 'p':
        case 'P':
                state->boards[N_PAWN] |= sq;
                break;
        case 'n':
        case 'N':
                state->boards[N_KNIGHT] |= sq;
                break;
        case 'b':
        case 'B':
                state->boards[N_BISHOP] |= sq;
                break;
        case 'r':
        case 'R':
                state->boards[N_ROOK] |= sq;
                break;
        case 'q':
        case 'Q':
                state->boards[N_QUEEN] |= sq;
                break;
        case 'k':
        case 'K':
                state->boards[N_KING] |= sq;
                break;
        }
        state->boards[N_OCCUPIED] |= sq;
}

/*
 * Set Position
 *
 * DESCRIPTION:
 *      Initialize a position described by the provided FEN string.
 */
void setpos(struct position *state, char *fenstr) {
        int rank = 7;
        int file = 0;
        
        char c;
        for (int i = 0; i < 10; ++i) { state->boards[i] = 0; }
        while ((c = *fenstr) != ' ') {
                if (c == '/') {
                        --rank;
                        file = 0;
                } else if (c > '0' && c <= '9') {
                        file += (c - '0');
                } else {
                        U64 sq = 1ull << ((8 * rank) + file);
                        putpiece(state, c, sq);
                        ++file;
                }
                ++fenstr;
        }
        state->boards[N_EMPTY] = (~state->boards[N_OCCUPIED]);
        assert((state->boards[N_OCCUPIED] & state->boards[N_EMPTY]) == 0);
        ++fenstr;

        state->side = *fenstr == 'w' ? WHITE : BLACK;
        assert(*fenstr == 'w' || *fenstr == 'b');
        fenstr += 2;

        state->rights = NO_CASTLING;
        assert(*fenstr != ' ');
        while ((c = *fenstr) != ' ') {
                switch (c) {
                case 'K':
                        state->rights |= WHITE_OO;
                        break;
                case 'Q':
                        state->rights |= WHITE_OOO;
                        break;
                case 'k':
                        state->rights |= BLACK_OO;
                        break;
                case 'q':
                        state->rights |= BLACK_OOO;
                        break;
                }
                ++fenstr;
        }
        ++fenstr;

        state->eptarget = NULL_SQ;
        assert(*fenstr != ' ');
        if (*fenstr != '-') {
                assert(*fenstr >= 'a' && *fenstr <= 'z');
                rank = *fenstr - 'a';
                ++fenstr;
                assert(*fenstr >= '1' && *fenstr <= '9');
                file = *fenstr - '1';
                state->eptarget = (8 * rank) + file;
        }
        fenstr += 2;

        state->rule50 = 0;
        assert(*fenstr != ' ');
        while ((c = *fenstr) != ' ') {
                assert(*fenstr >= '0' && *fenstr <= '9');
                state->rule50 += (state->rule50 * 10) + (c - '0');
                ++fenstr;
        }
        ++fenstr;

        state->plynb = 0;
        assert(*fenstr != ' ' && *fenstr != '\0');
        while((c = *fenstr) != '\0') {
                assert(*fenstr >= '0' && *fenstr <= '9');
                state->plynb += (state->plynb * 10) + (c - '0');
                ++fenstr;
        }
}
