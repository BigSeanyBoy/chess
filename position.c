#include "position.h"

/*
 * Distance to the Edge
 *
 * DESCRIPTION:
 * 	Calculate the distance to the edge from the specified square in all
 * 	directions.
 */
void edgedist(int edges[], int sq) {
	int north = 7 - (sq / 8);
	int east = 7 - (sq % 8);
	int south = sq / 8;
	int west = sq % 8;

	assert((north + south) == 7);
	assert((east + west) == 7);

	edges[0] = min(north, east);
	edges[1] = min(south, east);
	edges[2] = min(south, west);
	edges[3] = min(north, west);
}

/*
 * Initialize Ray Struct
 *
 * DESCRIPTION:
 * 	Calculate rays by direction and square. This function should be called
 * 	once on program startup so the same instance may be used and rays are
 * 	not recalculated each time sliding piece attacks are generated.
 */
void initrays(struct raylookup *rays) {
	for (int sq = 0; sq < 64; ++sq) {
		U64 pos = 1ull << sq;
		U64 rankmask = RANK_1 << (8 * (sq / 8));

		rays->north[sq] = (FILE_A << sq) & ~pos;
		assert((rays->north[sq] & ~(FILE_A << (sq % 8))) == 0);
		rays->east[sq] = (RANK_1 << sq) & rankmask & ~pos;
		assert((rays->east[sq] & (~rankmask)) == 0);
		rays->south[sq] = (FILE_H >> (63 - sq)) & ~pos;
		assert((rays->south[sq] & ~(FILE_H >> ((63 - sq) % 8))) == 0);
		rays->west[sq] = (RANK_8 >> (63 - sq)) & rankmask & ~pos;
		assert((rays->west[sq] & (~rankmask)) == 0);

		int edges[4];
		edgedist(edges, sq);

		rays->northeast[sq] = 0;
		for (int i = 1; i <= edges[0]; ++i) {
			rays->northeast[sq] |= pos << (9 * i);
		}

		rays->southeast[sq] = 0;
		for (int i = 1; i <= edges[1]; ++i) {
			rays->southeast[sq] |= pos >> (7 * i);
		}

		rays->southwest[sq] = 0;
		for (int i = 1; i <= edges[2]; ++i) {
			rays->southwest[sq] |= pos >> (9 * i);
		}

		rays->northwest[sq] = 0;
		for (int i = 1; i <= edges[3]; ++i) {
			rays->northwest[sq] |= pos << (7 * i);
		}
        }
}

/*
 * Put Piece
 *
 * DESCRIPTION:
 *      Insert the specified piece into the proper bitboards based on the
 *      provided character descriptor and square.
 */
void putpiece(struct position *state, char c, U64 sq) {
        state->boards[isupper(c) ? WHITE : BLACK] |= sq;
        switch (c) {
        case 'p':
        case 'P':
                state->boards[PAWN] |= sq;
                break;
        case 'n':
        case 'N':
                state->boards[KNIGHT] |= sq;
                break;
        case 'b':
        case 'B':
                state->boards[BISHOP] |= sq;
                break;
        case 'r':
        case 'R':
                state->boards[ROOK] |= sq;
                break;
        case 'q':
        case 'Q':
                state->boards[QUEEN] |= sq;
                break;
        case 'k':
        case 'K':
                state->boards[KING] |= sq;
                break;
        }
        state->boards[OCCUPIED] |= sq;
}

/*
 * Set Position
 *
 * DESCRIPTION:
 *      Initialize a position described by the provided FEN string.
 */
void setpos(struct position *state, char *fenstr) {
        initrays(&(state->rays));
        for (int i = 0; i < 256; ++i) { (state->movelist)[i] = 0; }

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
        state->boards[EMPTY] = (~state->boards[OCCUPIED]);
        assert((state->boards[OCCUPIED] & state->boards[EMPTY]) == 0);
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
