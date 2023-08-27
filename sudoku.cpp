#include "sudoku.hpp"

#include <iostream>

SudokuBoard::SudokuBoard() {
    for (int i = 0; i < size; ++i) {
        gameBoard[i] = new char[size]{0};
    }
}

SudokuBoard::~SudokuBoard() {
    for (int i = 0; i < size; ++i) {
        delete gameBoard[i];
    }
}

void SudokuBoard::print(std::ostream &out) const {
    for (int i = 0; i < size; ++i) {
        if (i && (i % (size / 3) == 0)) {
            for (int i = 0; i < size * 4 / 3 - 1; ++i) {
                out << "===";
            }

            out << '\n';
        }

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