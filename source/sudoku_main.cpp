#include <iostream>

#include "sudoku.h"

int getIntInput() {
    std::string input;

    std::cin >> input;

    return stoi(input);
}

int getValueInput(std::string prompt) {
    int returnValue;
    while (true) {
        try {
            std::cout << '\n' << prompt << '\n';

            returnValue = getIntInput();

            if (returnValue >= 0) {
                return returnValue;
            }
            std::cout << "input valid number that is above or equal to 0, or less than or equal to the size of the board" << '\n';
        } catch (const std::invalid_argument &e) {
            std::cout << '\n';
            std::cout << "invalid input, please input an integer!" << std::endl;
            std::cout << '\n';
        }
    }
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
    while (true) {
        try {
            std::cout << '\n'
                        << "Choose an option:" << '\n'
                        << "1: Input a Value into a grid space" << '\n'
                        << "2: Remove a Value from a grid space" << '\n'
                        << "3: Reprint board" << '\n'
                        << "4: show wrong gridspaces in board" << '\n'
                        << "5: submit board" << std::endl;

            int input = getIntInput();

            switch(input)
            {
                case 1:
                    return "valueInput";
                case 2:
                    return "removeValue";
                case 3:
                    return "printBoard";
                case 4:
                    return "showWrongGridSpaces";
                case 5:
                    return "submitBoard";
                default:
                    std::cout << "please input a valid option between, and including, 1 and 5" << std::endl;
            }
        } catch (const std::invalid_argument &e) {
            std::cout << '\n';
            std::cout << "invalid input, please input an integer!" << std::endl;
            std::cout << '\n';
        }
    }
}

void userInsertNumber(SudokuBoard &mainGame) {
    int row;
    int col;
    int value;

    while (true) {
        try {
            row = getValueInput("Please input a row to insert that value into that is above 0, or less than or equal to the size of the board, " + std::to_string(mainGame.getBoardSize()) + 
                                ".\n Input 0 if you want to cancel this");

            if (!row) return;

            col = getValueInput("Please input a column to insert that value into that is above 0, or less than or equal to the size of the board, " + std::to_string(mainGame.getBoardSize()) + 
                                ".\n Input 0 if you want to cancel this");

            if (!col) return;

            value = getValueInput("Please input a value to insert that is above 0, or less than or equal to the size of the board, " + std::to_string(mainGame.getBoardSize()) + 
                                ".\n Input 0 if you want to cancel this");

            if (!value) return;

            mainGame.playerInsertNumber(value, row, col);
        } catch (ValueOutOfBounds &e) {
            std::cout << '\n' << e.what() << '\n';
        } catch (GridPositionAlreadyTaken &e) {
            std::cout << '\n' << e.what() << '\n';
        }
    }
}

void userRemoveNumber(SudokuBoard &mainGame) {
    int row;
    int col;


} 

int main() {
    std::string userInput;

    SudokuBoard mainGame = promptGameCreation();

    for(int i = 0; i < 5; ++i) {
        std::cout << mainGame << std::endl;

        userInput = getUserOption();

        if (userInput == "printBoard") {
            continue;
        } else if (userInput == "valueInput") {
            userInsertNumber(mainGame);
        }
    }
}