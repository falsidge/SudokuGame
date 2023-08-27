#ifndef SUDOKU_HPP
#define SUDOKU_HPP

constexpr int BOARDSIZE = 9;

class SudokuBoard {
public:
    SudokuBoard();

    SudokuBoard(const SudokuBoard &s);

    SudokuBoard &operator=(const SudokuBoard &s);


    SudokuBoard(SudokuBoard &&s);

    SudokuBoard &operator=(SudokuBoard &&s);

    ~SudokuBoard();

private:
    int gameBoard[BOARDSIZE];
};

#endif