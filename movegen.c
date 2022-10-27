#include "./movegen.h"

// Pawn Pushes.
U64 WhiteSinglePushTargets(U64 pawns, U64 empty) {
        return north(pawns) & empty;
}

U64 WhiteDoublePushTargets(U64 pawns, U64 empty) {
        U64 single_push = w_single_push_targets(pawns, empty);
        return north(single_push) & empty & kRank4;
}

U64 BlackSinglePushTargets(U64 pawns, U64 empty) {
        return south(pawns) & empty;
}

U64 BlackDoublePushTargets(U64 pawns, U64 empty) {
        U64 single_push = b_single_push_targets(pawns, empty);
        return south(single_push) & empty & kRank5;
}

// Pawn Attacks.
U64 WhitePawnAttackEast(U64 pawns) {
        return north_east(pawns) & (~kFileA);
}

U64 WhitePawnAttackWest(U64 pawns) {
        return north_west(pawns) & (~kFileH);
}

U64 BlackPawnAttackEast(U64 pawns) {
        return south_east(pawns) & (~kFileA);
}

U64 BlackPawnAttackWest(U64 pawns) {
        return south_west(pawns) & (~kFileH);
}

// Pawn Captures.
U64 WhitePawnCaptureEast(U64 pawns, U64 bpieces) {
        return w_pawn_attack_east(pawns) & bpieces;
}

U64 WhitePawnCaptureWest(U64 pawns, U64 bpieces) {
        return w_pawn_attack_west(pawns) & bpieces;
}

U64 BlackPawnCaptureEast(U64 pawns, U64 wpieces) {
        return b_pawn_attack_east(pawns) & wpieces;
}

U64 BlackPawnCaptureWest(U64 pawns, U64 wpieces) {
        return b_pawn_attack_west(pawns) & wpieces;
}
