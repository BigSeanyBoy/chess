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
}

void TestFEN() {
  TestFENEmpty();
  TestFENStart();
  TestFENFirstMove();
  TestFENRandom();
}

void TestingSuite() {
  TestFEN();
  printf("%s[PASSED]%s FEN Import Tests\n", GREEN, DEFAULT);
}
