#include "bitboard.h"

/* 
 * Pawn Single Push
 * 
 * DESCRIPTION:
 *      Calculate pawn single push targets.
 */
U64 push(U64 pawns, U64 empty, enum color side) {
        U64 shift;
        if (side == WHITE) {
                shift = north(pawns) & empty;
                assert(shift == ((pawns << 8) & empty));
                assert((shift & RANK_2) == 0);
        } else {
                shift = south(pawns) & empty;
                assert(shift == ((pawns >> 8) & empty));
                assert((shift & RANK_7) == 0);
        }
        return shift;
}

/* 
 * Pawn Double Push
 *
 * DESCRIPTION:
 *      Calculate pawn double push targets.
 */
U64 dblpush(U64 pawns, U64 empty, enum color side) {
        U64 dblshift = push(pawns, empty, side);
        dblshift = push(dblshift, empty, side);
        if (side == WHITE) {
                dblshift &= RANK_4;
                assert((dblshift & (~RANK_4)) == 0);
        } else {
                dblshift &= RANK_5;
                assert((dblshift & (~RANK_5)) == 0);
        }
        return dblshift;
}

/* 
 * Pawn Attack
 *
 * DESCRIPTION:
 *      Calculate pawn attack targets.
 */
U64 pattack(U64 pawns, U64 enemies, enum color side) {
        U64 targets = 0;
        if (side == WHITE) {
                targets |= northeast(pawns) & enemies;
                assert((targets & ((~enemies) | FILE_A)) == 0);
                targets |= northwest(pawns) & enemies;
                assert((targets & ((~enemies) | FILE_H)) == 0);
        } else {
                targets |= southeast(pawns) & enemies;
                assert((targets & ((~enemies) | FILE_A)) == 0);
                targets |= southwest(pawns) & enemies;
                assert((targets & ((~enemies) | FILE_H)) == 0);
        }
        return targets;
}

/*
 * Pawn Moves
 *
 * DESCRIPTION:
 *      Calculate all pawn targets in a given position.
 */
U64 pmoves(U64 pawns, U64 enemies, U64 empty, enum color side) {
        U64 targets = 0;
        targets |= push(pawns, empty, side);
        targets |= dblpush(pawns, empty, side);
        targets |= pattack(pawns, enemies, side);
        return targets;
}

/*
 * Knight Moves
 *
 * DESCRIPTION:
 *      Calculate all knight targets in a given position. 
 */
U64 nmoves(U64 knights, U64 allies) {
        U64 targets = 0;
        U64 eshift = east(knights);
        U64 wshift = west(knights);
        targets |= ((eshift | wshift) << 16) & (~allies);
        assert(targets == ((knights << 15 | knights << 17) & (~allies)));
        targets |= ((eshift | wshift) >> 16) & (~allies);
        assert(targets == ((knights >> 15 | knights >> 17) & (~allies)));
        eshift = east(eshift);
        wshift = west(wshift);
        targets |= ((eshift | wshift) << 8) & (~allies);
        assert(targets == ((knights << 6 | knights << 10) & (~allies)));
        targets |= ((eshift | wshift) >> 8) & (~allies);
        assert(targets == ((knights >> 6 | knights >> 10) & (~allies)));
        assert((targets & allies) == 0);
        return targets;
}

/*
 * Distance to the Edge
 *
 * DESCRIPTION:
 *      Calculate the distance to the edge from the specified square in all
 *      directions.
 */
void edgedist(int edges[], int sq) {
        int north = 7 - (sq / 8);
        int east = 7 - (sq % 8);
        int south = sq / 8;
        int west = sq % 8;

        assert((north + south) == 7);
        assert((east + west) == 7);

        edges[0] = min(north, east);
        edges[1] = min(south, west);
        edges[2] = min(south, west);
        edges[3] = min(north, west);
}

/*
 * Initialize Ray Struct
 *
 * DESCRIPTION:
 *      Calculate rays by direction and square. This function should be called
 *      once on program startup so the same instance may be used and rays are
 *      not recalculated each time sliding piece attacks are generated.
 */
void initrays(struct raylookup *rays) {
        for (int sq = 0; sq < 64; ++sq) {
                U64 pos = 1 << sq;
                int rankmask = RANK_1 << (8 * (sq / 8));

                rays->north[sq] = (FILE_A << sq) & ~pos;
                assert((rays->north[sq] & ~(FILE_A << (sq % 8))) == 0);
                rays->east[sq] = (RANK_1 << sq) & rankmask & ~pos;
                assert((rays->east[sq] & (~rankmask)) == 0);
                rays->south[sq] = (FILE_H >> (63 - sq)) & ~pos;
                assert((rays->south[sq] & ~(FILE_H >> ((63 - sq) % 8))) == 0);
                rays->west[sq] = (RANK_8 >> (63 - sq)) & rankmask & ~pos;
                assert((rays->east[sq] & (~rankmask)) == 0);

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
