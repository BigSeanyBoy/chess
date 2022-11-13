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
        struct raylookup *rays; 
        rays = (struct raylookup *)malloc(sizeof(struct raylookup));
        initrays(rays);
        state->rays = rays;

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
 * Make En Passant
 *
 * DESCRIPTION:
 *      Remove the target pawn from the board during an en passant capture.
 */
void makeep(enum square dest, struct position *state) {
        U64 destbb = 1ull << dest;
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

        state->boards[flip(state->side)] ^= destbb;
        state->boards[PAWN] ^= destbb;
        state->boards[OCCUPIED] ^= destbb;
        state->piecelist[dest] = NO_PIECE;
}

/*
 * Make Castle
 *
 * DESCRIPTION:
 *      Handle the rook movement for a castling move.
 */
void makecastle(enum square dest, struct position *state) {
        int csource = NO_PIECE;
        U64 csbb = 0;
        int cdest = NO_PIECE;
        U64 cdbb = 0;

        switch(dest) {
        case G1:
                csource = H1;
                csbb = 1ull << csource;
                cdest = F1;
                cdbb = 1ull << cdest;

                state->rights ^= WHITE_OO;
                assert((state->rights & WHITE_OO) == 0);
                break;
        case C1:
                csource = A1;
                csbb = 1ull << csource;
                cdest = D1;
                cdbb = 1ull << cdest;
        
                state->rights ^= WHITE_OOO;
                assert((state->rights & WHITE_OOO) == 0);
                break;
        case G8:
                csource = H8;
                csbb = 1ull << csource;
                cdest = F8;
                cdbb = 1ull << cdest;

                state->rights ^= BLACK_OO;
                assert((state->rights & BLACK_OO) == 0);
                break;
        case C8:
                csource = A8;
                csbb = 1ull << csource;
                cdest = D8;
                cdbb = 1ull << cdest;

                state->rights ^= BLACK_OOO;
                assert((state->rights & BLACK_OOO) == 0);
                break;
        default:
                break;
        }

        state->boards[ROOK] ^= csbb;
        state->boards[state->side] ^= csbb;
        state->boards[OCCUPIED] ^= csbb;
        state->piecelist[csource] = NO_PIECE;

        state->boards[ROOK] |= cdbb;
        state->boards[state->side] |= cdbb;
        state->boards[OCCUPIED] |= cdbb;
        state->piecelist[cdest] = ROOK;
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
        if (state->side == BLACK) { ++(state->plynb); }

        enum square source = (move >> 6) & 63;
        assert(source < 64);
        U64 sourcebb = 1ull << source;
        assert(sourcebb != 0);

        enum square dest = move & 63;
        assert(dest < 64);
        U64 destbb = 1ull << dest;
        assert(destbb != 0);

        enum piece attacker = state->piecelist[source];
        enum piece target = state->piecelist[dest];

        if (attacker != PAWN && target == NO_PIECE) {
                ++(state->rule50);
        } else {
                state->rule50 = 0;
        }

        if (attacker == PAWN) {
                int dist = source - dest;
                if (abs(dist) == 16) {
                        state->eptarget = mid(source, dest);
                        assert(state->eptarget != NULL_SQ);
                }
        }

        state->boards[state->side] ^= sourcebb;
        state->boards[attacker] ^= sourcebb;
        state->boards[OCCUPIED] ^= sourcebb;
        state->piecelist[source] = NO_PIECE;

        if ((move & MOVETYPE_MASK) == PROMOTION) {
                attacker = (move & PROMO_MASK) + KNIGHT;
                assert(attacker > PAWN && attacker < KING);
        }

        state->boards[state->side] |= destbb;
        state->boards[attacker] |= destbb;
        state->boards[OCCUPIED] |= destbb;
        state->piecelist[dest] = attacker;

        if ((move & MOVETYPE_MASK) == EN_PASSANT) {
                makeep(dest, state);
        }

        if (target != NO_PIECE) {
                state->boards[flip(state->side)] &= (~destbb);
                state->boards[target] &= (~destbb);
        }

        if ((move & MOVETYPE_MASK) == CASTLING) {
                makecastle(dest, state);
        }

        state->boards[EMPTY] = ~(state->boards[OCCUPIED]);
        state->side = flip(state->side);
}

/*
 * Copy
 *
 * DESCRIPTION:
 *      Deep copy positional information from one state to another. The
 *      raylookup is copied as a pointer since there is no need to recompute
 *      the rays.
 */
void copy(struct position *state, struct position *copy) {
        copy->rays = state->rays;
        
        for (int i = 0; i < 64; ++i) {
                copy->piecelist[i] = state->piecelist[i];
        }

        for (int i = 0; i < 10; ++i) {
                copy->boards[i] = state->boards[i];
        }

        copy->side = state->side;
        copy->rights = state->rights;
        copy->eptarget = state->eptarget;
        copy->rule50 = state->rule50;
        copy->plynb = state->plynb;
}
