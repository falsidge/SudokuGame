#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <iosfwd>

constexpr int GRIDSIZE = 3;

class SudokuBoard {
public:
    SudokuBoard();

    SudokuBoard(const SudokuBoard &s);

    SudokuBoard &operator=(const SudokuBoard &s);

    SudokuBoard(SudokuBoard &&s);

    SudokuBoard &operator=(SudokuBoard &&s);

    ~SudokuBoard();

    void insertNumber(int num, int row, int col);

    void print(std::ostream &out) const;
private:
    void printHeader(std::ostream &out) const;

    bool valueInRange(int value) const;

    int size = GRIDSIZE * 3;
    char* gameBoard[GRIDSIZE * 3];
};

class ValueOutOfBounds: public std::exception {
public:
    ValueOutOfBounds(const std::string &msg = "");

    const char* what();
private:
    std::string message = "Given game value out of bounds!: ";
};

#endif