#include <iostream>

#include "sudoku.h"

void test() {
    SudokuBoard game = SudokuBoard();

    game.print(std::cout);

    game.insertAnchoredNumber(4, 6, 7);

    game.insertAnchoredNumber(1, 1, 1);

    game.print(std::cout);
}

int main() {
    test();
}