#include "sudoku.h"

#include <iostream>
#include <unordered_set>
#include <string>
#include <climits>

const int UPPER_LIMIT = INT_MAX;

SudokuBoard::SudokuBoard() {
    gameBoard = new int*[size];

    for (int i = 0; i < size; ++i) {
        gameBoard[i] = new int[size]{0};
    }

    madeNotUsingNew = false;
}

SudokuBoard::SudokuBoard(int** exampleBoard) {
    gameBoard = exampleBoard;
    madeNotUsingNew = true;
}

SudokuBoard::~SudokuBoard() {
    if (madeNotUsingNew) return;

    for (int i = 0; i < size; ++i) {
        delete gameBoard[i];
    }
    delete gameBoard;
}

int** SudokuBoard::getGameBoard(){
    return gameBoard;
}

std::unordered_set<int> SudokuBoard::getAnchoredcoor() {
    return anchoredCoor;
}

void SudokuBoard::print(std::ostream &out) const {
    printHeader(out);

    for (int i = 0; i < size; ++i) {
        if (i && (i % (size / 3) == 0)) {
            out << "  ";

            for (int k = 0; k < size * 4 / 3 - 1; ++k) {
                out << "===";
            }

            out << '\n';
        }

        out << i + 1 << "|";

        for(int j = 0; j < size; ++j) {
            if (j && (j % (size / 3) == 0)) {
                out << "|||";
            }

            if (gameBoard[i][j]) {
                out << ' ' << gameBoard[i][j] << ' ';
            } else {
                out << " x ";
            }
        }

        out << '\n';
    }
}

bool SudokuBoard::isConsecutiveSetsSolved(int rowDelta, int colDelta) const {
    int limiter = 0;
    for(int row = 0, col = 0;
        valueInRange(row + 1) && valueInRange(col + 1) && UPPER_LIMIT > limiter;
        row += rowDelta, col += colDelta, ++limiter) {
        
        if (!isSetOfNumbersSolved(row, col, colDelta, rowDelta)) return false;
    }

    if (limiter == UPPER_LIMIT) return false;

    return true;
}

bool SudokuBoard::isSetOfNumbersSolved(int row, int col, int rowDelta, int colDelta) const {
    if (rowDelta > 0) row = 0;
    if (colDelta > 0) col = 0;

    std::unordered_set<int> rowColSet;

    int limiter = 0;

    for(;valueInRange(row + 1) && valueInRange(col + 1) && UPPER_LIMIT > limiter;
        row += rowDelta, col += colDelta, ++limiter) {
        if (!gameBoard[row][col]) return false;
        if (rowColSet.find(gameBoard[row][col]) != rowColSet.end()) return false;
        rowColSet.insert(gameBoard[row][col]);
    }

    if (limiter == UPPER_LIMIT) return false;

    return true;
}

bool SudokuBoard::areAllGridsSolved() const {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (!isSingleGridSolved(i, j)) return false;
        }
    }

    return true;
}

bool SudokuBoard::isSingleGridSolved(int gridRow, int gridCol) const {
    if(gridRow < 0 || gridRow >= 3) throw ValueOutOfBounds("GridRow out of bounds " + std::to_string(gridRow));
    if(gridCol < 0 || gridCol >= 3) throw ValueOutOfBounds("GridCol out of bounds " + std::to_string(gridCol));

    int gridSize = size / 3;

    gridRow *= gridSize;
    gridCol *= gridSize;

    std::unordered_set<int> rowColSet;

    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (!gameBoard[gridRow + i][gridCol + j]) return false;
            if (rowColSet.find(gameBoard[gridRow + i][gridCol + j]) != rowColSet.end()) return false;
            rowColSet.insert(gameBoard[gridRow + i][gridCol + j]);
        }
    }

    return true;
}

bool SudokuBoard::isTheWholeBoardSolved() const {
    
}

void SudokuBoard::insertAnchoredNumber(int num, int row, int col) {
    checkRowColVal(num, row, col);

    gameBoard[row - 1][col - 1] = num;
    anchoredCoor.insert(calGridNumber(row, col));
}

void SudokuBoard::playerInsertNumber(int num, int row, int col) {
    checkRowColVal(num, row, col);

    if (!isGridAnchored(row, col)) {
        throw GridPositionAlreadyTaken("Position in sudoku grid already taken at row: " + std::to_string(row) + " and col: " + std::to_string(col));
    }

    gameBoard[row - 1][col - 1] = num;
}

void SudokuBoard::printHeader(std::ostream &out) const {
    out << "  ";
    for (int i = 0; i < size; ++i) {
        if (i && (i % (size / 3) == 0)) {
            out << "   ";
        }

        out << ' ' << i + 1 << ' ';
    }

    out << '\n';

    out << "  ";
    for (int i = 0; i < size; ++i) {
        if (i && (i % (size / 3) == 0)) {
            out << "   ";
        }

        out << "---";
    }

    out << '\n';
}

bool SudokuBoard::valueInRange(int value) const {
    return (0 < value && value <= size);
}

void SudokuBoard::checkRowColVal(int num, int row, int col) const {
    if (!valueInRange(num)) throw ValueOutOfBounds("The value inserted into the board is out of bounds/invalid : " + num);

    if (!valueInRange(row)) throw ValueOutOfBounds("The given row is out of bounds/invalid : " + row);

    if (!valueInRange(col)) throw ValueOutOfBounds("The given col is out of bounds/invalid : " + col);
}

bool SudokuBoard::isGridAnchored(int row, int col) {
    return (anchoredCoor.find(calGridNumber(row, col)) == anchoredCoor.end());
}

int SudokuBoard::calGridNumber(int row, int col) const {
    return (row - 1) * (size) + col - 1;
}