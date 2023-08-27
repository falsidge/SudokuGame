#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <iosfwd>

constexpr int BOARDSIZE = 9;

class SudokuBoard {
public:
    SudokuBoard();

    SudokuBoard(const SudokuBoard &s);

    SudokuBoard &operator=(const SudokuBoard &s);


    SudokuBoard(SudokuBoard &&s);

    SudokuBoard &operator=(SudokuBoard &&s);

    ~SudokuBoard();

    void print(std::ostream &out) const;

private:
    int size = BOARDSIZE;
    int* gameBoard[BOARDSIZE];
};

#endif