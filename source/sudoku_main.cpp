#include <iostream>

#include "sudoku.h"

int getIntInput() {
    std::string input;

    std::cin >> input;

    return stoi(input);
}

SudokuBoard promptGameCreation() {
    while (true) {
        try {
            std::cout << "How many squares would you like one of the 3x3 grids to have? (minimum of size of 1, maximum size of 99)" << std::endl;

            int gridSize = getIntInput();

            std::cout << '\n';

            return SudokuBoard(gridSize);
        }catch (const std::invalid_argument &e) {
            std::cout << '\n';
            std::cout << "invalid input, please input an integer!" << std::endl;
            std::cout << '\n';
        }catch (ValueOutOfBounds &e){
            std::cout << '\n';
            std::cout << e.what() << std::endl;
            std::cout << '\n';
        }
    }
}

std::string getUserOption() {
    std::cout << '\n'
                << "Choose an option:" << '\n'
                << "1: Input a Value into a grid space" << '\n'
                << "2: Remove a Value from a grid space" << '\n'
                << "3: Reprint board" << '\n'
                << "4: show wrong gridspaces in board" << '\n'
                << "5: submit board for review" << std::endl;

    int input = getIntInput();
}

int main() {
    SudokuBoard mainGame = promptGameCreation();

    std::cout << mainGame << std::endl;
}