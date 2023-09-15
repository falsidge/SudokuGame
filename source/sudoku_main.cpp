#include <iostream>

#include "sudoku.h"

SudokuBoard promptGameCreation() {
    while (true) {
        try {
            std::cout << "How many squares would you like one of the 3x3 grids to have? (minimum of size of 1, maximum size of 99)" << std::endl;

            int gridSize = getIntInput();

            std::cout << '\n';

            return SudokuBoard(gridSize);
        } catch (ValueOutOfBounds &e){
            std::cout << e.what() << std::endl;
            std::cout << '\n';
        }
        std::cin.clear();
    }
}

int getIntInput() {
    std::string input;

    std::cin >> input;

    return stoi(input);
}

int main() {
    SudokuBoard mainGame = promptGameCreation();

    std::cout << mainGame << std::endl;
}