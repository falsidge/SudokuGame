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

TEST(SudokuBoardOutOfBounds, AnchoredNumberOutOfBounds) {
    SudokuBoard game = SudokuBoard();

    game.insertAnchoredNumber(9, 5, 4);

    game.insertAnchoredNumber(7, 8, 9);

    game.insertAnchoredNumber(3, 5, 7);

    int expectedBoard[9][9] = {{0,0,0, 0,0,0, 0,0,0},
                               {0,0,0, 0,0,0, 0,0,0},
                               {0,0,0, 0,0,0, 0,0,0},
                               {0,0,0, 0,0,0, 0,0,0},
                               {0,0,0, 9,0,0, 3,0,0},
                               {0,0,0, 0,0,0, 0,0,0},
                               {0,0,0, 0,0,0, 0,0,0},
                               {0,0,0, 0,0,0, 0,0,7},
                               {0,0,0, 0,0,0, 0,0,0}};

    auto board = game.getGameBoard();

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            EXPECT_EQ(board[i][j], expectedBoard[i][j]);
        }
    }

    EXPECT_THROW({
        game.insertAnchoredNumber(3, 9, 10);
    }, ValueOutOfBounds);

    EXPECT_THROW({
        game.insertAnchoredNumber(0, 3, 6);
    }, ValueOutOfBounds);

    EXPECT_THROW({
        game.insertAnchoredNumber(3, 4, -100);
    }, ValueOutOfBounds);
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

TEST(SudokuBoardOutOfBounds, PlayerInsertedNumberOutOfBounds) {
    SudokuBoard game = SudokuBoard();

    game.playerInsertNumber(5, 7, 8);

    game.playerInsertNumber(3, 4, 9);

    game.playerInsertNumber(9, 4, 2);

    int expectedBoard[9][9] = {{0,0,0, 0,0,0, 0,0,0},
                               {0,0,0, 0,0,0, 0,0,0},
                               {0,0,0, 0,0,0, 0,0,0},
                               {0,9,0, 0,0,0, 0,0,3},
                               {0,0,0, 0,0,0, 0,0,0},
                               {0,0,0, 0,0,0, 0,0,0},
                               {0,0,0, 0,0,0, 0,5,0},
                               {0,0,0, 0,0,0, 0,0,0},
                               {0,0,0, 0,0,0, 0,0,0}};

    auto board = game.getGameBoard();

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            EXPECT_EQ(board[i][j], expectedBoard[i][j]);
        }
    }

    EXPECT_THROW({
        game.playerInsertNumber(5, 0, 9);
    }, ValueOutOfBounds);

    EXPECT_THROW({
        game.playerInsertNumber(5, 10, 9);
    }, ValueOutOfBounds);

    EXPECT_THROW({
        game.playerInsertNumber(-100, 4, 5);
    }, ValueOutOfBounds);
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

    game.playerInsertNumber(3, 5, 2);
    game.playerInsertNumber(8, 8, 5);
    game.playerInsertNumber(1, 6, 3);
    game.playerInsertNumber(8, 4, 5);
    game.playerInsertNumber(6, 5, 6);
    game.playerInsertNumber(7, 7, 9);
    game.playerInsertNumber(9, 3, 9);

    expectedBoard[4][1] = 3;
    expectedBoard[7][4] = 8;
    expectedBoard[5][2] = 1;
    expectedBoard[3][4] = 8;
    expectedBoard[4][5] = 6;
    expectedBoard[6][8] = 7;
    expectedBoard[2][8] = 9;

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            EXPECT_EQ(board[i][j], expectedBoard[i][j]);
        }
    }

    EXPECT_THROW({
        game.playerInsertNumber(9, 3, 6);
    }, GridPositionAlreadyTaken);

    EXPECT_THROW({
        game.playerInsertNumber(3, 8, 9);
    }, GridPositionAlreadyTaken);

    EXPECT_THROW({
        game.playerInsertNumber(6, 3, 8);
    }, GridPositionAlreadyTaken);

    game.playerInsertNumber(7, 8, 5);
    game.playerInsertNumber(7, 6, 3);

    expectedBoard[7][4] = 7;
    expectedBoard[5][2] = 7;

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            EXPECT_EQ(board[i][j], expectedBoard[i][j]);
        }
    }
} 