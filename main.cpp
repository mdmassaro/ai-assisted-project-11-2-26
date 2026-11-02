#include "square.h"

#include <iostream>
#include <sstream>
#include <string>

namespace {

const int BOARD_SIZE = 9;
const int BOX_SIZE = 3;

void drawHorizontalBorder() {
    std::cout << "+-------+-------+-------+\n";
}

void drawBoard(const Square board[BOARD_SIZE][BOARD_SIZE]) {
    drawHorizontalBorder();
    for (int row = 0; row < BOARD_SIZE; ++row) {
        std::cout << "| ";
        for (int column = 0; column < BOARD_SIZE; ++column) {
            board[row][column].draw();
            if (column % BOX_SIZE == BOX_SIZE - 1) {
                std::cout << " | ";
            } else {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
        if (row % BOX_SIZE == BOX_SIZE - 1) {
            drawHorizontalBorder();
        }
    }
}

bool hasConflict(const Square board[BOARD_SIZE][BOARD_SIZE],
                 int row, int column, int value) {
    for (int index = 0; index < BOARD_SIZE; ++index) {
        if (index != column && board[row][index].getValue() == value) {
            return true;
        }
        if (index != row && board[index][column].getValue() == value) {
            return true;
        }
    }

    const int boxRow = (row / BOX_SIZE) * BOX_SIZE;
    const int boxColumn = (column / BOX_SIZE) * BOX_SIZE;
    for (int r = boxRow; r < boxRow + BOX_SIZE; ++r) {
        for (int c = boxColumn; c < boxColumn + BOX_SIZE; ++c) {
            if ((r != row || c != column) &&
                board[r][c].getValue() == value) {
                return true;
            }
        }
    }
    return false;
}

bool isComplete(const Square board[BOARD_SIZE][BOARD_SIZE]) {
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int column = 0; column < BOARD_SIZE; ++column) {
            if (board[row][column].getValue() == 0) {
                return false;
            }
        }
    }
    return true;
}

void printHelp() {
    std::cout << "Enter a move as: row column value (each 1-9).\n"
              << "Use value 0 to clear a cell, or enter b to redraw the board.\n"
              << "Enter h for help or q to quit. Given clues cannot be changed.\n";
}

} // namespace

int main() {
    const int puzzle[BOARD_SIZE][BOARD_SIZE] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    Square board[BOARD_SIZE][BOARD_SIZE];
    bool fixed[BOARD_SIZE][BOARD_SIZE];
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int column = 0; column < BOARD_SIZE; ++column) {
            board[row][column] = Square(row + 1, column + 1, puzzle[row][column]);
            fixed[row][column] = puzzle[row][column] != 0;
        }
    }

    std::cout << "Welcome to Terminal Sudoku!\n";
    printHelp();

    std::string line;
    while (true) {
        drawBoard(board);
        std::cout << "Move> ";
        if (!std::getline(std::cin, line)) {
            std::cout << "\nGoodbye!\n";
            return 0;
        }

        std::istringstream input(line);
        std::string command;
        input >> command;
        if (command.empty()) {
            continue;
        }
        if (command == "q" || command == "quit") {
            std::cout << "Goodbye!\n";
            return 0;
        }
        if (command == "h" || command == "help") {
            printHelp();
            continue;
        }
        if (command == "b" || command == "board") {
            continue;
        }

        std::istringstream move(line);
        int row;
        int column;
        int value;
        char extra;
        if (!(move >> row >> column >> value) || (move >> extra)) {
            std::cout << "Please enter a command or a move as: row column value.\n";
            continue;
        }
        if (row < 1 || row > BOARD_SIZE ||
            column < 1 || column > BOARD_SIZE ||
            value < 0 || value > BOARD_SIZE) {
            std::cout << "Row and column must be 1-9; value must be 0-9.\n";
            continue;
        }

        --row;
        --column;
        if (fixed[row][column]) {
            std::cout << "That cell is a fixed clue and cannot be changed.\n";
            continue;
        }
        if (value != 0 && hasConflict(board, row, column, value)) {
            std::cout << "That move conflicts with its row, column, or 3x3 box.\n";
            continue;
        }

        board[row][column].setValue(value);
        if (isComplete(board)) {
            drawBoard(board);
            std::cout << "Congratulations! You solved the Sudoku!\n";
            return 0;
        }
    }
}