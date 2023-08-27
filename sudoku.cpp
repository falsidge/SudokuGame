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

void SudokuBoard::insertNumber(int num, int row, int col) {
    if (!(valueInRange(num) && 
        valueInRange(row) &&
        valueInRange(col))) {

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
    return 0 < value <= size;
}


//exception functions

ValueOutOfBounds::ValueOutOfBounds(const std::string &msg = "") {
    message += msg;
}

const char* ValueOutOfBounds::what() {
    return (message).c_str();
}