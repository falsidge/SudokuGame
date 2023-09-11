#include <iostream>

#include "sudoku.h"

void test() {
    SudokuBoard game = SudokuBoard(3);

    game.print(std::cout);

    game.insertAnchoredNumber(4, 6, 7);

    game.insertAnchoredNumber(1, 1, 1);

    game.insertAnchoredNumber(10, 8, 1);

    game.print(std::cout);
}

int main() {
    test();
}