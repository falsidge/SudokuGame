#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <iosfwd>
#include <unordered_set>
#include <string>

constexpr int GRIDSIZE = 3;

class SudokuBoard {
public:
    SudokuBoard();

    SudokuBoard(int** exampleBoard);

    SudokuBoard(const SudokuBoard &s);

    SudokuBoard &operator=(const SudokuBoard &s);

    SudokuBoard(SudokuBoard &&s);

    SudokuBoard &operator=(SudokuBoard &&s);

    ~SudokuBoard();

    int** getGameBoard();

    std::unordered_set<int> getAnchoredcoor();

    void insertAnchoredNumber(int num, int row, int col);

    //add later, supposed to make it so you can't change numbers from the previous function
    void playerInsertNumber(int num, int row, int col);

    void print(std::ostream &out) const;


    //solving subfunctions (public for testing purposes)

    bool isConsecutiveSetsSolved(int rowDelta, int colDelta) const;
    bool isSetOfNumbersSolved(int row, int col, int rowDelta, int colDelta) const;

    bool isSingleGridSolved(int gridRow, int gridCol) const;
private:
    void printHeader(std::ostream &out) const;

    bool valueInRange(int value) const;

    void checkRowColVal(int num, int row, int col) const;

    bool isGridAnchored(int row, int col);

    int calGridNumber(int row, int col) const;

    int size = GRIDSIZE * 3;
    int** gameBoard;
    std::unordered_set<int> anchoredCoor;
    bool madeNotUsingNew;
};

class GridPositionAlreadyTaken: public std::exception {
public:
    GridPositionAlreadyTaken(const std::string &msg = "") {
        message += msg;
    }

    std::string what() {
        return (message).c_str();
    }
private:
    std::string message = "Grid Position in board already taken!: ";
};

class ValueOutOfBounds: public std::exception {
public:
    ValueOutOfBounds(const std::string &msg = "") {
        message += msg;
    }

    std::string what() {
        return (message).c_str();
    }
private:
    std::string message = "Given game value out of bounds!: ";
};

#endif