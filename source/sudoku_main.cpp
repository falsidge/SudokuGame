#include <iostream>

#include "sudoku.h"

constexpr double EASY_PERCENTAGE_MISSING = 0.54;
constexpr double MEDIUM_PERCENTAGE_MISSING = 0.62;
constexpr double HARD_PERCENTAGE_MISSING = 0.70;
constexpr double EXPERT_PERCENTAGE_MISSING = 0.72;

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

bool getPlayAgain() {
    while (true) {
        std::cout << "'\nWould you like to play again?\nY for yes\nN for no" << std::endl;
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

void createGameDifficulty(SudokuBoard &mainGame) {
    while (true) {
        int difficulty = getValueInput("Please choose a difficulty of the generated SudokuBoard!\n1 :Easy\n2 :Medium\n3 :Hard\n4 :Expert\n");


        switch(difficulty) {
            case 1:
                mainGame.generateNewPlayableBoard(EASY_PERCENTAGE_MISSING);
                return;

            case 2:
                mainGame.generateNewPlayableBoard(MEDIUM_PERCENTAGE_MISSING);
                return;

            case 3:
                mainGame.generateNewPlayableBoard(HARD_PERCENTAGE_MISSING);
                return;

            case 4:
                mainGame.generateNewPlayableBoard(EXPERT_PERCENTAGE_MISSING);
                return;

            default:
                std::cout << '\n' << "please input a valid difficult level between and including 1 through 4\n" << std::endl;
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
            std::cout << mainGame << std::endl;
            row = getValueInput("Please input a row to insert that value into that is above 0, or less than or equal to the size of the board, " + std::to_string(mainGame.getBoardSize()) + 
                                ".\n Input 0 if you want to cancel this");

            if (!row) return;

            std::cout << mainGame << std::endl;
            col = getValueInput("Please input a column to insert that value into that is above 0, or less than or equal to the size of the board, " + std::to_string(mainGame.getBoardSize()) + 
                                ".\n Input 0 if you want to cancel this");

            if (!col) return;

            value = getValueInput("Please input a value to insert that is above 0, or less than or equal to the size of the board, " + std::to_string(mainGame.getBoardSize()) + 
                                ".\n Input 0 if you want to cancel this");

            if (!value) return;

            mainGame.playerInsertNumber(value, row, col);
            return;

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

    while (true) {
        try {
            std::cout << mainGame << std::endl;
            row = getValueInput("Please input a row to insert that value into that is above 0, or less than or equal to the size of the board, " + std::to_string(mainGame.getBoardSize()) + 
                                ".\n Input 0 if you want to cancel this");

            if (!row) return;

            std::cout << mainGame << std::endl;
            col = getValueInput("Please input a column to insert that value into that is above 0, or less than or equal to the size of the board, " + std::to_string(mainGame.getBoardSize()) + 
                                ".\n Input 0 if you want to cancel this");

            if (!col) return;

            mainGame.playerRemoveNumber(row, col);
            return;

        } catch(ValueOutOfBounds &e) {
            std::cout << '\n' << e.what() << '\n';
        } catch (GridPositionAlreadyTaken &e) {
            std::cout << '\n' << e.what() << '\n';
        }
    }
} 

int createPlayGame() {
    std::string userInput;

    SudokuBoard mainGame = promptGameCreation();

    bool isBoardSolved = mainGame.isTheWholeBoardSolved();

    std::cout << mainGame << std::endl;

    createGameDifficulty(mainGame);

    std::cout << mainGame << std::endl;

    while(!isBoardSolved) {

        userInput = getUserOption();

        if (userInput == "valueInput") {
            userInsertNumber(mainGame);
        } else if (userInput == "removeValue") {
            userRemoveNumber(mainGame);
        } else if (userInput == "showWrongGridSpaces") {
            mainGame.print(std::cout, true);
            continue;
        } else if (userInput == "submitBoard") {
            isBoardSolved = mainGame.isTheWholeBoardSolved();

            if (isBoardSolved) {
                std::cout << mainGame << std::endl;

                std::cout << '\n'
                            << "Congradulations!!!" << '\n'
                            << "You solved the sudoku board!" << std::endl;

                continue;
            } else {
                mainGame.print(std::cout, true);

                std::cout << '\n'
                            << "Sorry there are wrong values present in the board." << '\n'
                            << "Please Try Again" << std::endl;
                continue;
            }
        }

        std::cout << mainGame << std::endl;
    }
}

int main() {
    bool isPlayingGame = true;

    while (isPlayingGame) {
        createPlayGame();


    }
}