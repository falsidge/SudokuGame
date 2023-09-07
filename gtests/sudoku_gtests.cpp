#include <gtest/gtest.h>
#include "../source/sudoku.h"

TEST(SudokuBoardSetUp, CreatingBoard) {
    SudokuBoard game = SudokuBoard();

    auto board = game.getGameBoard();

    int expectedBoard[9][9] = {{0,0,0, 0,0,0, 0,0,0},
                               {0,0,0, 0,0,0, 0,0,0},
                               {0,0,0, 0,0,0, 0,0,0},
                               {0,0,0, 0,0,0, 0,0,0},
                               {0,0,0, 0,0,0, 0,0,0},
                               {0,0,0, 0,0,0, 0,0,0},
                               {0,0,0, 0,0,0, 0,0,0},
                               {0,0,0, 0,0,0, 0,0,0},
                               {0,0,0, 0,0,0, 0,0,0}};

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            EXPECT_EQ(board[i][j], expectedBoard[i][j]);
        }
    }
}

TEST(SudokuBoardSetUp, AnchoredNumberPlacement) {
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

    auto anchoredCoorSet = game.getAnchoredcoor();

    auto board = game.getGameBoard();

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            EXPECT_EQ(board[i][j], expectedBoard[i][j]);
        }
    }

    EXPECT_NE(anchoredCoorSet.find((6 - 1) * 9 + (7 - 1)), anchoredCoorSet.end());
    EXPECT_NE(anchoredCoorSet.find(0), anchoredCoorSet.end());
    EXPECT_NE(anchoredCoorSet.find((3 - 1) * 9 + (7 - 1)), anchoredCoorSet.end());

    EXPECT_EQ(anchoredCoorSet.find((4 - 1) * 9 + (8 - 1)), anchoredCoorSet.end());
}

TEST(SudokuBoardSetUp, PlayerNumberPlacement) {
    SudokuBoard game = SudokuBoard();

    game.playerInsertNumber(6, 8, 4);

    game.playerInsertNumber(9, 4, 7);

    game.playerInsertNumber(3, 8, 5);

    int expectedBoard[9][9] = {{0,0,0, 0,0,0, 0,0,0},
                               {0,0,0, 0,0,0, 0,0,0},
                               {0,0,0, 0,0,0, 0,0,0},
                               {0,0,0, 0,0,0, 9,0,0},
                               {0,0,0, 0,0,0, 0,0,0},
                               {0,0,0, 0,0,0, 0,0,0},
                               {0,0,0, 0,0,0, 0,0,0},
                               {0,0,0, 6,3,0, 0,0,0},
                               {0,0,0, 0,0,0, 0,0,0}};

    auto board = game.getGameBoard();

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            EXPECT_EQ(board[i][j], expectedBoard[i][j]);
        }
    }
}


TEST(SudokuBoardSetUp, PlayerAnchoredInteractionPlacement) {
    SudokuBoard game = SudokuBoard();

    game.insertAnchoredNumber(1, 6, 1);
    game.insertAnchoredNumber(2, 3, 5);
    game.insertAnchoredNumber(3, 3, 8);
    game.insertAnchoredNumber(4, 3, 6);
    game.insertAnchoredNumber(5, 8, 9);
    game.insertAnchoredNumber(6, 2, 1);
    game.insertAnchoredNumber(7, 1, 4);
    game.insertAnchoredNumber(8, 7, 1);
    game.insertAnchoredNumber(9, 5, 4);

    int expectedBoard[9][9] = {{0,0,0, 7,0,0, 0,0,0},
                               {6,0,0, 0,0,0, 0,0,0},
                               {0,0,0, 0,2,4, 0,3,0},
                               {0,0,0, 0,0,0, 0,0,0},
                               {0,0,0, 9,0,0, 0,0,0},
                               {1,0,0, 0,0,0, 0,0,0},
                               {8,0,0, 0,0,0, 0,0,0},
                               {0,0,0, 0,0,0, 0,0,5},
                               {0,0,0, 0,0,0, 0,0,0}};

    auto board = game.getGameBoard();

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            EXPECT_EQ(board[i][j], expectedBoard[i][j]);
        }
    }
} 