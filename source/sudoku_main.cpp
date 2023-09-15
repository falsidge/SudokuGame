#include <iostream>

#include "sudoku.h"

SudokuBoard promptGameCreation() {
    while (true) {
        try {
            std::cout << "How many squares would you like one of the 3x3 grids to have? (minimum of size of 1, maximum size of 99)" << std::endl;

            int gridSize;
            std::cin >> gridSize;

            return SudokuBoard(gridSize);
        } catch (const std::invalid_argument& e){
            std::cout << "Sorry there was an issue with your input: " << std::endl;
            std::cout << e.what() << std::endl;
            std::cout << "please try again" << std::endl;
            std::cout << '\n';
        }
    }
}

int main() {
    SudokuBoard mainGame = promptGameCreation();
}