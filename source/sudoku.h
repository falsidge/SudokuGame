#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <iosfwd>
#include <set>
#include <string>

class SudokuBoard {
public:
    SudokuBoard(int gridSize = 3);

    //used for testing
    SudokuBoard(int** exampleBoard);

    SudokuBoard(const SudokuBoard &s);

    SudokuBoard &operator=(const SudokuBoard &s);

    SudokuBoard(SudokuBoard &&s);

    SudokuBoard &operator=(SudokuBoard &&s);

    ~SudokuBoard();

    int** getGameBoard();

    std::set<int> getAnchoredcoor();

    void insertAnchoredNumber(int num, int row, int col);

    void playerInsertNumber(int num, int row, int col);

    void print(std::ostream &out) const;

    bool isTheWholeBoardSolved() const;
    //solving subfunctions (public for testing purposes)

    bool isConsecutiveSetsSolved(int rowDelta, int colDelta) const;
    bool isSetOfNumbersSolved(int row, int col, int rowDelta, int colDelta) const;

    bool areAllGridsSolved() const;
    bool isSingleGridSolved(int gridRow, int gridCol) const;

    //generating newBoard class (public for testing purposes)
    class newBoardGenerator {
    protected:
        newBoardGenerator(int** newGameBoard, int size);
    private:
        std::set<int>* rows;
        std::set<int>* cols;
        std::set<int>* grids;
        std::set<int> availableGrids;

        int** newGameBoard;
        int size;
        int numberOfAvailableGrids;
    };
private:

    void printHeader(std::ostream &out) const;

    bool valueInRange(int value) const;

    void checkRowColVal(int num, int row, int col) const;

    bool isGridAnchored(int row, int col);

    int calGridNumber(int row, int col) const;

    int size;
    int** gameBoard;
    std::set<int> anchoredCoor;
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