#include "../tests/unit.h"

void TestFENEmpty() {
  char *fenstr = "8/8/8/8/8/8/8/8 w - - 0 1";
  struct CBoard position;
  ImportFEN(&position, fenstr);

  for (int i = 0; i < 64; ++i) {
    assert(position.pieces[i] == 0);
  }
  assert(position.side == kWhite);
  assert(position.castling_rights == kNoCastling);
  assert(position.en_passant_target == kNullSquare);
  assert(position.halfmove_clock == 0);
  assert(position.move_number == 1);
}

void TestFENStart() {
  U8 testpos[64] = {12, 10, 11, 13, 14, 11, 10, 12,
                     9,  9,  9,  9,  9,  9,  9,  9,
                     0,  0,  0,  0,  0,  0,  0,  0,
                     0,  0,  0,  0,  0,  0,  0,  0,
                     0,  0,  0,  0,  0,  0,  0,  0,
                     0,  0,  0,  0,  0,  0,  0,  0,
                    17, 17, 17, 17, 17, 17, 17, 17,
                    20, 18, 19, 21, 22, 19, 18, 20};

  char *fenstr = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  struct CBoard position;
  ImportFEN(&position, fenstr);

  for (int i = 0; i < 64; ++i) {
    assert(position.pieces[i] == testpos[i]);
  }
  assert(position.side == kWhite);
  assert(position.castling_rights == kAnyCastling);
  assert(position.en_passant_target == kNullSquare);
  assert(position.halfmove_clock == 0);
  assert(position.move_number == 1);
}

void TestFENFirstMove() {
  U8 testpos[64] = {12, 10, 11, 13, 14, 11, 10, 12,
                     9,  9,  9,  9,  0,  9,  9,  9,
                     0,  0,  0,  0,  0,  0,  0,  0,
                     0,  0,  0,  0,  9,  0,  0,  0,
                     0,  0,  0,  0,  0,  0,  0,  0,
                     0,  0,  0,  0,  0,  0,  0,  0,
                    17, 17, 17, 17, 17, 17, 17, 17,
                    20, 18, 19, 21, 22, 19, 18, 20};

  char *fenstr = "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1";
  struct CBoard position;
  ImportFEN(&position, fenstr);

  for (int i = 0; i < 64; ++i) {
    assert(position.pieces[i] == testpos[i]);
  }
  assert(position.side == kBlack);
  assert(position.castling_rights == kAnyCastling);
  assert(position.en_passant_target == kE3);
  assert(position.halfmove_clock == 0);
  assert(position.move_number == 1);
}

void TestFENRandom() {
  U8 testpos[64] = {12,  0, 0, 0, 14, 0,  0, 12,
                     0,  0, 0, 0,  0, 0,  0,  0,
                     0,  0, 0, 0,  0, 0,  0,  0,
                     0,  0, 0, 0,  0, 0,  0, 11,
                     0,  0, 0, 0,  0, 0,  0,  0,
                     0,  0, 0, 0,  0, 0,  0,  0,
                     0, 19, 0, 0, 22, 0, 19, 21,
                    20,  0, 0, 0,  0, 0,  0, 20};

  char *fenstr = "r6r/1b2k1bq/8/8/7B/8/8/R3K2R b KQ - 3 2";
  struct CBoard position;
  ImportFEN(&position, fenstr);

  for (int i = 0; i < 64; ++i) {
    assert(position.pieces[i] == testpos[i]);
  }
  assert(position.side == kBlack);
  assert(position.castling_rights == kWhiteCastling);
  assert(position.en_passant_target == kNullSquare);
  assert(position.halfmove_clock == 3);
  assert(position.move_number == 2);
}

void TestDistanceFromEdge(struct MovementArrays *lookup) {
  U8 north, east, south, west;
  for (int i = 0; i < 64; ++i) {
    north = 7 - (i / 8);
    east = 7 - (i % 8);
    south = i / 8;
    west = i % 8;

    assert(lookup->edge_dist[kNorth][i] == north);
    assert(lookup->edge_dist[kEast][i] == east);
    assert(lookup->edge_dist[kSouth][i] == south);
    assert(lookup->edge_dist[kWest][i] == west);

    assert(lookup->edge_dist[kNorthEast][i] == min(north, east));
    assert(lookup->edge_dist[kSouthEast][i] == min(south, east));
    assert(lookup->edge_dist[kSouthWest][i] == min(south, west));
    assert(lookup->edge_dist[kNorthWest][i] == min(north, west));
  }
}

void TestWhitePawnMovement(struct MovementArrays *lookup) {
  U64 movement[64];
  for (int i = 0; i < 64; ++i) {
    movement[i] = 0;
    if (i / 8 == 0 || i / 8 == 7) {
      assert(lookup->white_pawns[i] == 0);
      continue;
    } else if (i / 8 == 1) {
      movement[i] += (1ull << (i + kOffsetN + kOffsetN));
    }

    if (lookup->edge_dist[kNorthWest][i]) {
      movement[i] += 1ull << (i + kOffsetNW);
    }
    if (lookup->edge_dist[kNorthEast][i]) {
      movement[i] += 1ull << (i + kOffsetNE);
    }
    movement[i] += 1ull << (i + kOffsetN);

    assert(lookup->white_pawns[i] == movement[i]);
  }
}

void TestBlackPawnMovement(struct MovementArrays *lookup) {
  U64 movement[64];
  for (int i = 0; i < 64; ++i) {
    movement[i] = 0;
    if (i / 8 == 0 || i / 8 == 7) {
      assert(lookup->black_pawns[i] == 0);
      continue;
    } else if (i / 8 == 6) {
      movement[i] += (1ull << (i + kOffsetS + kOffsetS));
    }

    if (lookup->edge_dist[kSouthWest][i]) {
      movement[i] += 1ull << (i + kOffsetSW);
    }
    if (lookup->edge_dist[kSouthEast][i]) {
      movement[i] += 1ull << (i + kOffsetSE);
    }
    movement[i] += 1ull << (i + kOffsetS);

    assert(lookup->black_pawns[i] == movement[i]);
  }
}

void TestFEN() {
  TestFENEmpty();
  TestFENStart();
  TestFENFirstMove();
  TestFENRandom();
}

void TestMovement() {
  struct MovementArrays lookup;
  InitMovementArrays(&lookup);

  TestDistanceFromEdge(&lookup);
  TestWhitePawnMovement(&lookup);
  TestBlackPawnMovement(&lookup);
}

void TestingSuite() {
  TestFEN();
  printf("%s[PASSED]%s FEN Import Tests\n", GREEN, DEFAULT);

  TestMovement();
  printf("%s[PASSED]%s Movement Lookup Tests\n", GREEN, DEFAULT);
}
