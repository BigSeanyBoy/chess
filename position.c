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
 * Inititalize Position
 *
 * DESCRIPTION:
 *      Initialize any position struct members that are not reset or updated
 *      with a new board position.
 */
void initpos(struct position *state) {
        struct raylookup *rays; 
        rays = (struct raylookup *)malloc(sizeof(struct raylookup));
        initrays(rays);
        state->rays = rays;
}

/*
 * Free Position
 *
 * DESCRIPTION:
 *      Free any manually allocated position struct members.
 */
void freepos(struct position *state) {
        free(state->rays);
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
                file = *fenstr - 'a';
                ++fenstr;
                assert(*fenstr >= '1' && *fenstr <= '9');
                rank = *fenstr - '1';
                state->eptarget = (8 * rank) + file;
        }
        while (*fenstr != ' ' && *fenstr != '\n') { ++fenstr; }

        state->rule50 = 0;
        state->plynb = 0;

        if (!(*fenstr >= '0' && *fenstr <= '9')) { return; }

        while ((c = *fenstr) != ' ') {
                assert(*fenstr >= '0' && *fenstr <= '9');
                state->rule50 += (state->rule50 * 10) + (c - '0');
                ++fenstr;
        }
        ++fenstr;

        assert(*fenstr != ' ' && *fenstr != '\0');
        while((c = *fenstr)) {
                if (c == ' ' || c == '\n' || c == '\0') { break; }
                assert(*fenstr >= '0' && *fenstr <= '9');
                state->plynb += (state->plynb * 10) + (c - '0');
                ++fenstr;
        }
}

/*
 * Print Position
 *
 * DESCRIPTION:
 *      Print the board based on the given position.
 */
void printpos(struct position *state) {
        printf("\n");
        for (int r = 7; r >= 0; --r) {
                printf(" %d | ", r + 1);
                for (int f = 0; f < 8; ++f) {
                        int sq = 8 * r + f;
                        U64 b = 1ull << sq;
                        U64 wb = state->boards[WHITE];

                        enum piece p = state->piecelist[sq];
                        enum color pc = wb & b ? WHITE : BLACK;

                        char c;
                        switch (p) {
                        case PAWN:
                                c = pc == WHITE ? 'P' : 'p';
                                break;
                        case KNIGHT:
                                c = pc == WHITE ? 'N' : 'n';
                                break;
                        case BISHOP:
                                c = pc == WHITE ? 'B' : 'b';
                                break;
                        case ROOK:
                                c = pc == WHITE ? 'R' : 'r';
                                break;
                        case QUEEN:
                                c = pc == WHITE ? 'Q' : 'q';
                                break;
                        case KING:
                                c = pc == WHITE ? 'K' : 'k';
                                break;
                        default:
                                c = '.';
                                break;
                        }

                        f == 7 ? printf("%c\n", c) : printf("%c ", c);
                }
        }
        printf("     ---------------\n");
        printf("     a b c d e f g h\n\n");
}

/*
 * Update Castling Rights
 *
 * DESCRIPTION:
 *      Remove castling rights based on whether a king or rook moves from it's
 *      initial position, or if a rook is captured from it's initial position.
 */
void updatecastle(struct position *state, enum square sq) {
        switch (sq) {
        case H1:
                state->rights &= ~WHITE_OO;
                break;
        case E1:
                state->rights &= ~WHITE_CASTLE;
                break;
        case A1:
                state->rights &= ~WHITE_OOO;
                break;
        case H8:
                state->rights &= ~BLACK_OO;
                break;
        case E8:
                state->rights &= ~BLACK_CASTLE;
                break;
        case A8:
                state->rights &= ~BLACK_OOO;
                break;
        default:
                break;
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
        assert(dest >= 0 && dest < 64);

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

                state->rights &= ~WHITE_CASTLE;
                assert((state->rights & WHITE_CASTLE) == 0);
                break;
        case C1:
                csource = A1;
                csbb = 1ull << csource;
                cdest = D1;
                cdbb = 1ull << cdest;
        
                state->rights &= ~WHITE_CASTLE;
                assert((state->rights & WHITE_CASTLE) == 0);
                break;
        case G8:
                csource = H8;
                csbb = 1ull << csource;
                cdest = F8;
                cdbb = 1ull << cdest;

                state->rights &= ~BLACK_CASTLE;
                assert((state->rights & BLACK_CASTLE) == 0);
                break;
        case C8:
                csource = A8;
                csbb = 1ull << csource;
                cdest = D8;
                cdbb = 1ull << cdest;

                state->rights &= ~BLACK_CASTLE;
                assert((state->rights & BLACK_CASTLE) == 0);
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
int make(U16 move, struct position *state) {
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
        assert(attacker != NO_PIECE);

        if (attacker != PAWN && target == NO_PIECE) {
                ++(state->rule50);
        } else {
                state->rule50 = 0;
        }

        if (state->rights != NO_CASTLING) {
                if (attacker == KING) { updatecastle(state, source); }
                if (attacker == ROOK) { updatecastle(state, source); }
                if (target == ROOK) { updatecastle(state, dest); }
        }

        state->eptarget = NULL_SQ;
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

        int promo = 0;
        if ((move & MOVETYPE_MASK) == PROMOTION) {
                promo = 1;
                attacker = ((move >> 12) & 3ull) + KNIGHT;
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
                if (attacker != target) {
                        state->boards[target] &= (~destbb);
                }
        }

        if ((move & MOVETYPE_MASK) == CASTLING) {
                makecastle(dest, state);
        }

        state->boards[EMPTY] = ~(state->boards[OCCUPIED]);

        if (incheck(state, NULL_SQ)) { return 0; }

        state->side = flip(state->side);
        return 1;
}

/*
 * In Check
 *
 * DESCRIPTION:
 * 	Test if the current side's king is in check.
 */
int incheck(struct position *state, enum square checksq) {
	U64 king;
	if (checksq == NULL_SQ) {
		king = state->boards[KING] & state->boards[state->side];
		checksq = __builtin_ctzll(king);
	} else {
		king = 1ull << checksq;
	}
	assert(king != 0);
        U64 enemies = state->boards[flip(state->side)];
	assert((king & enemies) == 0);

	U64 penemy = state->boards[PAWN] & enemies;
	U64 nenemy = state->boards[KNIGHT] & enemies;
	U64 benemy = state->boards[BISHOP] & enemies;
	U64 renemy = state->boards[ROOK] & enemies;
	U64 qenemy = state->boards[QUEEN] & enemies;

	U64 pcheck = pattack(king, penemy, state->side);
	U64 ncheck = ntargets(checksq, state);
        U64 bcheck = btargets(checksq, state);
        U64 rcheck = rtargets(checksq, state);
	U64 qcheck = bcheck | rcheck;

        if ((pcheck & penemy) ||
	    (ncheck & nenemy) ||
	    (bcheck & benemy) ||
	    (rcheck & renemy) ||
	    (qcheck & qenemy)) {
		return 1;
	}

        return 0;
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
