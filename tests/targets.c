#include "targets.h"

/* 
 * Pawn Targets Test
 * 
 * DESCRIPTION:
 *      Test pawn pattern and attack calculations.
 */
void ptargets() {
        U64 pawns, enemybb, empty;

        pawns = 0xbf00;
	enemybb = 0x2904d20000;
	empty = 0xffffffd6fb2d40ff;
	assert(pmoves(pawns, enemybb, empty, WHITE) == 0x297f0000);
	printf("%s[PASSED]%s white pawn moves\n", GREEN, DEFAULT);

        pawns = 0xbf000000000000;
        enemybb = 0xd20429000000;
        empty = 0xff402dfbd6ffffff;
        assert(pmoves(pawns, enemybb, empty, BLACK) == 0x7f2900000000);
	printf("%s[PASSED]%s black pawn moves\n", GREEN, DEFAULT);
}

/* 
 * Test Driver
 *
 * DESCRIPTION:
 *      Runs all target calculation tests.
 */
void testdriver() {
        ptargets();
}
