#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <iosfwd>
#include <unordered_set>

constexpr int GRIDSIZE = 3;

class SudokuBoard {
public:
    SudokuBoard();

    SudokuBoard(const SudokuBoard &s);

    SudokuBoard &operator=(const SudokuBoard &s);

    SudokuBoard(SudokuBoard &&s);

    SudokuBoard &operator=(SudokuBoard &&s);

    ~SudokuBoard();

    void insertAnchoredNumber(int num, int row, int col);

    //add later, supposed to make it so you can't change numbers from the previous function
    void playerInsertNumber(int num, int row, int col);

    void print(std::ostream &out) const;
private:
    void printHeader(std::ostream &out) const;

    bool valueInRange(int value) const;

    void checkRowColVal(int num, int row, int col) const;

    int size = GRIDSIZE * 3;
    int* gameBoard[GRIDSIZE * 3];
    std::unordered_set<std::string> anchoredCoor = {};
};

class ValueOutOfBounds: public std::exception {
public:
    ValueOutOfBounds(const std::string &msg = "");

    const char* what();
private:
    std::string message = "Given game value out of bounds!: ";
};

#endif