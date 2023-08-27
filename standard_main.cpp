#include <iostream>

#include "sudoku.hpp"
#include "sudoku.cpp"

void test() {
    SudokuBoard game = SudokuBoard();

    game.print(std::cout);
}

int main() {
    test();
}