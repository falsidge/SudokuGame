#include "sudoku.h"

#include <iostream>
#include <set>
#include <string>
#include <climits>
#include <random>
#include <cmath>
#include <unordered_map>

const int UPPER_LIMIT = INT_MAX;

SudokuBoard::SudokuBoard(int gridSize) {
    if (gridSize < 1 || gridSize > 99) {
        throw ValueOutOfBounds("Value given for board is out of bounds: " + std::to_string(gridSize));
    }

    size = gridSize * gridSize;
    gridSize = gridSize;

    gameBoard = new int*[size];

    for (int i = 0; i < size; ++i) {
        gameBoard[i] = new int[size]{0};
    }

    madeNotUsingNew = false;
}

SudokuBoard::SudokuBoard(int** exampleBoard) {
    //size of given board HAS to be 9 x 9 (mainly for testing purposes)
    size = 9;

    gameBoard = exampleBoard;
    madeNotUsingNew = true;
}

SudokuBoard::~SudokuBoard() {
    if (madeNotUsingNew) return;

    for (int i = 0; i < size; ++i) {
        delete gameBoard[i];
    }
    delete gameBoard;
}

int** SudokuBoard::getGameBoard(){
    return gameBoard;
}

std::set<int> SudokuBoard::getAnchoredcoor() {
    return anchoredCoor;
}

int SudokuBoard::getBoardSize() const {
    return size;
}

void SudokuBoard::insertAnchoredNumber(int num, int row, int col) {
    checkRowColVal(num, row, col);

    gameBoard[row - 1][col - 1] = num;
    anchoredCoor.insert(calGridNumber(row - 1, col - 1));
}

void SudokuBoard::playerInsertNumber(int num, int row, int col) {
    checkRowColVal(num, row, col);

    if (!isGridAnchored(row - 1, col - 1)) {
        throw GridPositionAlreadyTaken("Position in sudoku grid already taken by anchored number at row: " + std::to_string(row) + " and col: " + std::to_string(col));
    }

    gameBoard[row - 1][col - 1] = num;
}

void SudokuBoard::playerRemoveNumber(int row, int col) {
    checkRowColVal(1, row, col);

    if (!isGridAnchored(row - 1, col - 1)) {
        throw GridPositionAlreadyTaken("Position in sudoku grid is an anchored number, can not be removed; row: " + std::to_string(row) + ", column: " + std::to_string(col));
    }

    gameBoard[row - 1][col - 1] = 0;
}

void SudokuBoard::print(std::ostream &out, bool markWrongValues) const {
    printHeader(out);

    std::set<int> wrongGrids;
    
    if (markWrongValues) {
        wrongGrids = getAllWrongGrids();
    }

    auto tempIndex = wrongGrids.begin();

    for (int i = 0; i < size; ++i) {
        if (i && (i % gridSize == 0)) {
            out << "  " << adjustStringSize(' ');

            out << "======";
            for (int k = 0; k < size; ++k) {
                out << "===" << adjustStringSize('=');
            }

            out << '\n';
        }

        out << composeNumber(i + 1) << "|";

        for(int j = 0; j < size; ++j) {
            if (j && (j % gridSize == 0)) {
                out << "|||";
            }

            if (markWrongValues && tempIndex != wrongGrids.end() && calGridNumber(i, j) == *tempIndex) {
                out << returnNumberComposition(gameBoard[i][j], calGridNumber(i, j), true);
                ++tempIndex;
            } else {
                out << returnNumberComposition(gameBoard[i][j], calGridNumber(i, j), false);
            }
        }

        out << '\n';
    }
}

bool SudokuBoard::isTheWholeBoardSolved() const {
    return (isConsecutiveSetsSolved(0, 1) &&
            isConsecutiveSetsSolved(1, 0) &&
            areAllGridsSolved());
}

std::set<int> SudokuBoard::getAllWrongGrids() const {
    std::set<int> wrongGrids;

    std::set<int> tempSet = getWrongGridsInConsecutiveSets(1, 0);
    wrongGrids.insert(tempSet.begin(), tempSet.end());

    tempSet = getWrongGridsInConsecutiveSets(0, 1);
    wrongGrids.insert(tempSet.begin(), tempSet.end());

    tempSet = getAllWrongGridsInMacroGrids();
    wrongGrids.insert(tempSet.begin(), tempSet.end());

    return wrongGrids;
}

bool SudokuBoard::isConsecutiveSetsSolved(int rowDelta, int colDelta) const {
    int limiter = 0;
    for(int row = 0, col = 0;
        valueInRange(row + 1) && valueInRange(col + 1) && UPPER_LIMIT > limiter;
        row += rowDelta, col += colDelta, ++limiter) {
        
        if (!isSetOfNumbersSolved(row, col, colDelta, rowDelta)) return false;
    }

    if (limiter == UPPER_LIMIT) return false;

    return true;
}

bool SudokuBoard::isSetOfNumbersSolved(int row, int col, int rowDelta, int colDelta) const {
    if (rowDelta > 0) row = 0;
    if (colDelta > 0) col = 0;

    std::set<int> rowColSet;

    int limiter = 0;

    for(;valueInRange(row + 1) && valueInRange(col + 1) && UPPER_LIMIT > limiter;
        row += rowDelta, col += colDelta, ++limiter) {
        if (!gameBoard[row][col]) return false;
        if (rowColSet.find(gameBoard[row][col]) != rowColSet.end()) return false;
        rowColSet.insert(gameBoard[row][col]);
    }

    if (limiter == UPPER_LIMIT) return false;

    return true;
}

bool SudokuBoard::areAllGridsSolved() const {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (!isSingleGridSolved(i, j)) return false;
        }
    }

    return true;
}

bool SudokuBoard::isSingleGridSolved(int gridRow, int gridCol) const {
    if(gridRow < 0 || gridRow >= gridSize) throw ValueOutOfBounds("GridRow out of bounds " + std::to_string(gridRow));
    if(gridCol < 0 || gridCol >= gridSize) throw ValueOutOfBounds("GridCol out of bounds " + std::to_string(gridCol));

    gridRow *= gridSize;
    gridCol *= gridSize;

    std::set<int> rowColSet;

    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (!gameBoard[gridRow + i][gridCol + j]) return false;
            if (rowColSet.find(gameBoard[gridRow + i][gridCol + j]) != rowColSet.end()) return false;
            rowColSet.insert(gameBoard[gridRow + i][gridCol + j]);
        }
    }

    return true;
}

std::set<int> SudokuBoard::getWrongGridsInConsecutiveSets(int rowDelta, int colDelta) const {
    std::set<int> wrongGrids;

    int limiter = 0;

    for (int row = 0, col = 0; row < size && col < size && limiter < UPPER_LIMIT;
        row += rowDelta, col += colDelta, ++limiter) {
        std::set<int> tempSet = getWrongGridsInSet(row, col, colDelta, rowDelta);

        wrongGrids.insert(tempSet.begin(), tempSet.end());
    }

    return wrongGrids;
}

std::set<int> SudokuBoard::getWrongGridsInSet(int row, int col, int rowDelta, int colDelta) const {
    if (rowDelta > 0) row = 0;
    if (colDelta > 0) col = 0;
    
    int limiter = 0;

    std::unordered_map<int, int> valueAndGridSpace;
    std::set<int> wrongGrids;

    for (;valueInRange(row + 1) && valueInRange(col + 1) && limiter < UPPER_LIMIT;
        row += rowDelta, col += colDelta, ++limiter) {
        if (!gameBoard[row][col]) {
            wrongGrids.insert(calGridNumber(row, col));

        } else if (valueAndGridSpace.find(gameBoard[row][col]) != valueAndGridSpace.end()) {
            wrongGrids.insert(calGridNumber(row, col));
            wrongGrids.insert(valueAndGridSpace.find(gameBoard[row][col])->second);

        } else {
            valueAndGridSpace[gameBoard[row][col]] = calGridNumber(row, col);
        }
    }

    if (limiter == UPPER_LIMIT) throw ValueOutOfBounds("Limit reached in loop");

    return wrongGrids;
}

std::set<int> SudokuBoard::getAllWrongGridsInMacroGrids() const {
    std::set<int> wrongGrids;

    for(int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            std::set<int> tempSet = getWrongGridsInMacroGrid(i, j);

            wrongGrids.insert(tempSet.begin(), tempSet.end());
        }
    }

    return wrongGrids;
}

std::set<int> SudokuBoard::getWrongGridsInMacroGrid(int gridRow, int gridCol) const {
    if (gridRow < 0 || gridRow >= gridSize) throw ValueOutOfBounds("given grid row out of bounds " + std::to_string(gridRow));
    if (gridCol < 0 || gridCol >= gridSize) throw ValueOutOfBounds("given grid col out of bounds " + std::to_string(gridCol));

    int limiter = 0;

    std::unordered_map<int, int> valueAndGridSpace;
    std::set<int> wrongGrids;

    gridRow *= gridSize;
    gridCol *= gridSize;

    for (int i = 0; i < gridSize && limiter < UPPER_LIMIT; ++i) {
        for (int j = 0; j < gridSize && limiter < UPPER_LIMIT; ++j) {
            int row = gridRow + i;
            int col = gridCol + j;

            if (!gameBoard[row][col]) {
                wrongGrids.insert(calGridNumber(row, col));
            } else if (valueAndGridSpace.find(gameBoard[row][col]) != valueAndGridSpace.end()) {
                wrongGrids.insert(calGridNumber(row, col));
                wrongGrids.insert(valueAndGridSpace.find(gameBoard[row][col])->second);
            } else {
                valueAndGridSpace[gameBoard[row][col]] = calGridNumber(row, col);
            }

            ++limiter;
        }
    }

    if (limiter == UPPER_LIMIT) throw ValueOutOfBounds("Limit reached in loop");

    return wrongGrids;
}

std::string SudokuBoard::adjustStringSize(const char value) const {
    std::string returnValue = "";

    for(int i = 0; i < int(log10(size)); ++i) {
        returnValue = returnValue + value;
    }

    return returnValue;
}

std::string SudokuBoard::returnNumberComposition(int num, int gridCoor, bool markWrongValue) const {
    std::string mainReturn = composeNumber(num);

    if (markWrongValue) {
        return "*" + mainReturn + "*";
    } else if (anchoredCoor.size() > 0 && anchoredCoor.find(gridCoor) != anchoredCoor.end()) {
        return "[" + mainReturn + "]";
    } 
    return " " + mainReturn + " ";
}

std::string SudokuBoard::composeNumber(int n) const {
    int numOfDigits = int(log10(size));
    std::string mainReturn;

    if (n <= 0) {
        n = 1;
        mainReturn = "x";
    } else {
        mainReturn = std::to_string(n);
    }

    for (int i = 0; i < numOfDigits - int(log10(n)); ++i) {
        mainReturn = " " + mainReturn;
    }

    return mainReturn;
}

void SudokuBoard::printHeader(std::ostream &out) const {
    out << "  " << adjustStringSize(' ');

    for (int i = 0; i < size; ++i) {
        if (i && (i % gridSize == 0)) {
            out << "   ";
        }

        out << ' ' << composeNumber(i + 1) << ' ';
    }

    out << '\n';

    out << "  " << adjustStringSize(' ');

    for (int i = 0; i < size; ++i) {
        if (i && (i % gridSize == 0)) {
            out << "   ";
        }

        out << "---" << adjustStringSize('-');;

    }

    out << '\n';
}

bool SudokuBoard::valueInRange(int value) const {
    //doesn't include zero as values inside sudoku board that are valid are never zero
    return (0 < value && value <= size);
}

void SudokuBoard::checkRowColVal(int num, int row, int col) const {
    if (!valueInRange(num)) throw ValueOutOfBounds("The value inserted into the board is out of bounds/invalid : " + std::to_string(num));

    if (!valueInRange(row)) throw ValueOutOfBounds("The given row is out of bounds/invalid : " + std::to_string(row));

    if (!valueInRange(col)) throw ValueOutOfBounds("The given col is out of bounds/invalid : " + std::to_string(col));
}

bool SudokuBoard::isGridAnchored(int row, int col) {
    return (anchoredCoor.find(calGridNumber(row, col)) == anchoredCoor.end());
}

int SudokuBoard::calGridNumber(int row, int col) const {
    return (row) * (size) + col;
}

void SudokuBoard::generateNewPlayableBoard(double percentageEmpty) {
    if (percentageEmpty < 0 || percentageEmpty > 1) {
        throw ValueOutOfBounds("Number of removed values is either too large or too small");
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            gameBoard[i][j] = 0;
        }
    }

    anchoredCoor.clear();


    newBoardGenerator generator = newBoardGenerator(gameBoard, size);

    generator.createCompletedBoard();

    int numOfRemovedValues = int((size * size) * percentageEmpty + 0.5);
    anchoredCoor = generator.eraseNumOfSquares(numOfRemovedValues);
}

std::ostream &operator<<(std::ostream &out, const SudokuBoard &b) {
    b.print(out);

    return out;
}

SudokuBoard::newBoardGenerator::newBoardGenerator(int** newGameBoard, int size)
                : newGameBoard(newGameBoard), size(size), gridSize(int(sqrt(size))), numberOfAvailableGrids(size * size)
    {
        for(int i = 0; i < size * size; ++i) {
            allIndivGrids.insert(i);
        }

        for (int i = 1; i <= size; ++i) {
            allValues.insert(i);
        }

        rowValues = new std::set<int>[size];
        colValues = new std::set<int>[size];
    }

SudokuBoard::newBoardGenerator::~newBoardGenerator() {
    delete[] rowValues;
    delete[] colValues;
}

void SudokuBoard::newBoardGenerator::createCompletedBoard() {
    if (!size) return;

    std::set<int> **dp = new std::set<int>*[size];
    for(int i = 0; i < size; ++i) {
        dp[i] = new std::set<int>[size];
    }

    //backtracking algorithm, randomized for sudoku
    dp[0][0] = getAvailableNumberSet(0);
    for(int i = 0; i < size * size - 1;) {
        int row = calRowNumber(i);
        int col = calColNumber(i);

        int value = pickRanValidVal(dp[row][col]);

        if (value == -1) {
            --i;
            removeValueFromGridSpace(i, newGameBoard[calRowNumber(i)][calColNumber(i)]);
            continue;
        }

        dp[row][col].erase(value);
        insertValueIntoGridSpace(i, value);
        ++i;

        dp[calRowNumber(i)][calColNumber(i)] = getAvailableNumberSet(i);
    }
    insertValueIntoGridSpace(size * size - 1, 
                *dp[size-1][size-1].begin());
    //end of algorithm

    for(int i = 0; i < size; ++i) {
        delete[] dp[i];
    }
    delete[] dp;
}

std::set<int> SudokuBoard::newBoardGenerator::eraseNumOfSquares(int n) {
    std::set<int> remainingGridNumbers = allIndivGrids;

    if (n < 0 || n > size * size) {
        throw ValueOutOfBounds("Number of values erased too large, or too small");
    }

    for (int i = 0; i < n; ++i) {
        int gridNumber = pickRanValidVal(remainingGridNumbers);

        newGameBoard[calRowNumber(gridNumber)][calColNumber(gridNumber)] = 0;

        remainingGridNumbers.erase(gridNumber);
    }

    return remainingGridNumbers;
}

int SudokuBoard::newBoardGenerator::pickRanValidVal(std::set<int> &values) {
    if (!values.size()) return -1;

    std::random_device generator;
    std::mt19937 rng(generator());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(0, values.size() - 1);

    auto tempIndex = values.begin();

    std::advance(tempIndex, distribution(generator));

    return *tempIndex;
}

void SudokuBoard::newBoardGenerator::insertValueIntoGridSpace(int gridSpace, int value) {
    rowValues[calRowNumber(gridSpace)].insert(value);
    colValues[calColNumber(gridSpace)].insert(value);
    grids[calMacroGridCoor(gridSpace)].insert(value);

    newGameBoard[calRowNumber(gridSpace)][calColNumber(gridSpace)] = value;
}

void SudokuBoard::newBoardGenerator::removeValueFromGridSpace(int gridSpace, int value)
{
    rowValues[calRowNumber(gridSpace)].erase(value);
    colValues[calColNumber(gridSpace)].erase(value);
    grids[calMacroGridCoor(gridSpace)].erase(value);

    newGameBoard[calRowNumber(gridSpace)][calColNumber(gridSpace)] = 0;
}

std::set<int> SudokuBoard::newBoardGenerator::
    getAvailableNumberSet(int gridSpace) {
        std::set<int> unavailableValues;

        mergeTwoSets(unavailableValues, rowValues[calRowNumber(gridSpace)]);
        mergeTwoSets(unavailableValues, colValues[calColNumber(gridSpace)]);
        mergeTwoSets(unavailableValues, grids[calMacroGridCoor(gridSpace)]);

        std::set<int> availableValues = allValues;

        for (auto i = unavailableValues.begin(); i != unavailableValues.end(); ++i)
        {
            availableValues.erase(*i);
        }
        return availableValues;
}

void SudokuBoard::newBoardGenerator::
    mergeTwoSets(std::set<int> &target, std::set<int> const &given) const {
        for(auto i = given.begin(); i != given.end(); ++i) {
            target.insert(*i);
        }
}

int SudokuBoard::newBoardGenerator::calRowNumber(int gridSpace) const{
    return (gridSpace / size);
}

int SudokuBoard::newBoardGenerator::calColNumber(int gridSpace) const{
    return(gridSpace % size);
}

int SudokuBoard::newBoardGenerator::calMacroGridCoor(int gridSpace) const {
    int gridRow = (gridSpace / size) / (gridSize);
    int gridCol = (gridSpace % size) / (gridSize);

    return (gridRow * gridSize + gridCol);
}

int SudokuBoard::newBoardGenerator::calGridNumber(int row, int col) const {
    return ((row * size) + col);
}