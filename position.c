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
void putpiece(struct position *state, char c, int sq, U64 sqbb) {
        state->boards[isupper(c) ? WHITE : BLACK] |= sqbb;
        switch (c) {
        case 'p':
        case 'P':
                state->boards[PAWN] |= sqbb;
                state->piecelist[sq] = PAWN;
                break;
        case 'n':
        case 'N':
                state->boards[KNIGHT] |= sqbb;
                state->piecelist[sq] = KNIGHT;
                break;
        case 'b':
        case 'B':
                state->boards[BISHOP] |= sqbb;
                state->piecelist[sq] = BISHOP;
                break;
        case 'r':
        case 'R':
                state->boards[ROOK] |= sqbb;
                state->piecelist[sq] = ROOK;
                break;
        case 'q':
        case 'Q':
                state->boards[QUEEN] |= sqbb;
                state->piecelist[sq] = QUEEN;
                break;
        case 'k':
        case 'K':
                state->boards[KING] |= sqbb;
                state->piecelist[sq] = KING;
                break;
        }
        state->boards[OCCUPIED] |= sqbb;
}

/*
 * Set Position
 *
 * DESCRIPTION:
 *      Initialize a position described by the provided FEN string.
 */
void setpos(struct position *state, char *fenstr) {
        initrays(&(state->rays));

        state->history.idx = 0;
        for (int i = 0; i < 1024; ++i) { (state->history.list)[i] = 0; }

        state->moves.count = 0;
        for (int i = 0; i < 256; ++i) { (state->moves.list)[i] = 0; }

        for (int i = 0; i < 64; ++i) { state->piecelist[i] = NO_PIECE; }

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
                        int sq = (8 * rank) + file;
                        U64 sqbb = 1ull << sq;
                        putpiece(state, c, sq, sqbb);
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


/*
 * Make Move
 *
 * DESCRIPTION:
 *      Play the specified move by updating the position. This includes
 *      moving the relevant pieces to the proper locations, removing
 *      captured pieces from the board, updating the piece list,
 *      incrementing the halfmove clock (if necessary) and the move count,
 *      and recording castling rights and en passant targets.
 */
void make(U16 move, struct position *state) {
        assert(state->history.idx < 1024);
        state->history.list[state->history.idx] = move;
        ++state->history.idx;

        enum square source = (move >> 6) & 63;
        assert(source < 64);
        U64 sourcebb = 1ull << source;
        assert(sourcebb != NULL_SQ);

        enum square dest = move & 63;
        assert(dest < 64);
        U64 destbb = 1ull << dest;
        assert(destbb != NULL_SQ);

        enum piece attacker = state->piecelist[source];
        enum piece target = state->piecelist[dest];

        if (attacker == PAWN && abs(source - dest) > 15) {
                state->eptarget = mid(source, dest);
                assert(state->eptarget != NULL_SQ);
        }

        state->boards[state->side] ^= sourcebb;
        state->boards[attacker] ^= sourcebb;
        state->boards[OCCUPIED] ^= sourcebb;
        state->piecelist[source] = 0;

        if (move & PROMOTION) {
                attacker = ((move >> 12) & 3) + KNIGHT;
                assert(attacker > 2 && attacker < 7);
        }

        state->boards[state->side] |= destbb;
        state->boards[attacker] |= destbb;
        state->boards[OCCUPIED] |= destbb;
        state->piecelist[dest] = attacker;

        if (move & EN_PASSANT) {
                switch (state->side) {
                case WHITE:
                        destbb = destbb >> 8;
                        dest -= 8;
                        break;
                case BLACK:
                        destbb = destbb << 8;
                        dest += 8;
                        break;
                }
                assert(destbb);
                assert(dest >=0 && dest < 64);
                state->boards[OCCUPIED] ^= destbb;
                state->piecelist[dest] = 0;
        }

        if (target != NO_PIECE) {
                state->boards[flip(state->side)] &= (~destbb);
                state->boards[target] &= (~destbb);
        }

        if (move & CASTLING) {
                U64 csource = 0;
                U64 cdest = 0;
                switch(dest) {
                case G1:
                        csource = 1ull << H1;
                        cdest = 1ull << F1;
                        state->rights ^= WHITE_OO;
                        assert((state->rights & WHITE_OO) == 0);
                        break;
                case C1:
                        csource = 1ull << A1;
                        cdest = 1ull << D1;
                        state->rights ^= WHITE_OOO;
                        assert((state->rights & WHITE_OOO) == 0);
                        break;
                case G8:
                        csource = 1ull << H8;
                        cdest = 1ull << F8;
                        state->rights ^= BLACK_OO;
                        assert((state->rights & BLACK_OO) == 0);
                        break;
                case C8:
                        csource = 1ull << A8;
                        cdest = 1ull << D8;
                        state->rights ^= BLACK_OOO;
                        assert((state->rights & BLACK_OOO) == 0);
                        break;
                default:
                        break;
                }

                state->boards[ROOK] ^= csource;
                state->boards[state->side] ^= csource;
                state->boards[OCCUPIED] ^= sourcebb;

                state->boards[ROOK] |= cdest;
                state->boards[state->side] |= cdest;
                state->boards[OCCUPIED] |= destbb;
        }
        state->boards[EMPTY] = ~(state->boards[OCCUPIED]);
}
