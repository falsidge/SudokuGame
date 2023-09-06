#include "sudoku.h"

#include <iostream>
#include <unordered_set>
#include <string>

SudokuBoard::SudokuBoard() {
    for (int i = 0; i < size; ++i) {
        gameBoard[i] = new int[size]{0};
    }
}

SudokuBoard::~SudokuBoard() {
    for (int i = 0; i < size; ++i) {
        delete gameBoard[i];
    }
}

int** SudokuBoard::getGameBoard(){
    return gameBoard;
}

std::unordered_set<int> SudokuBoard::getAnchorcoors() {
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

void SudokuBoard::insertAnchoredNumber(int num, int row, int col) {
    try {
        checkRowColVal(num, row, col);

        gameBoard[row - 1][col - 1] = num;
        anchoredCoor.insert(calGridNumber(row, col));

    } catch (ValueOutOfBounds &e) {
        std::cout << "Problem inserting number :" << e.what() << std::endl;
    }
}

void SudokuBoard::playerInsertNumber(int num, int row, int col) {
    try {
        checkRowColVal(num, row, col);

        if (!isGridAnchored(row, col)) {
            throw GridPositionAlreadyTaken("Position in sudoku grid already taken at row: " + row + "and col: " + col);
        }

        gameBoard[row - 1][col - 1] = num;
    } catch (ValueOutOfBounds &e) {
        std::cout << "Problem inserting number :" << e.what() << std::endl;
    } catch (GridPositionAlreadyTaken &e) {
        std::cout << "Problem inserting number :" << e.what() << std::endl;
    }
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