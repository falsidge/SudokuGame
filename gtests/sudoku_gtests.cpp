#include <gtest/gtest.h>
#include "../source/sudoku.h"

TEST(SudokuLogic, AnchoredNumberPlacement) {
    SudokuBoard game = SudokuBoard();

    game.insertAnchoredNumber(4, 6, 7);

    game.insertAnchoredNumber(1, 1, 1);

    game.insertAnchoredNumber(7, 3, 7);

    int expectedBoard[9][9] = {{1,0,0, 0,0,0, 0,0,0},
                          {0,0,0, 0,0,0, 0,0,0},
                          {0,0,0, 0,0,0, 7,0,0},
                          {0,0,0, 0,0,0, 0,0,0},
                          {0,0,0, 0,0,0, 0,0,0},
                          {0,0,0, 0,0,0, 4,0,0},
                          {0,0,0, 0,0,0, 0,0,0},
                          {0,0,0, 0,0,0, 0,0,0},
                          {0,0,0, 0,0,0, 0,0,0}};

    auto board = game.getGameBoard();

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            EXPECT_EQ(board[i][j], expectedBoard[i][j]);
        }
    }
}