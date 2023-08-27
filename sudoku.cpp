#include "sudoku.hpp"

#include <iostream>

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

void SudokuBoard::print(std::ostream &out) const {
    for (int i = 1; i <= size; ++i) {
        for(int j = 1; j <= size; ++j) {
            
        }
    }
}