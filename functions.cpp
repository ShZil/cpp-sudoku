#include <iostream>
#include <vector>
#include <algorithm>
#include "functions.h"

std::vector<std::vector<std::vector<int>>> getBoard() {
    const int width = 9;
    const int height = 9;
    std::vector<std::vector<std::vector<int>>> result = {};

    for (int y = 0; y < height; y++) {
        std::vector<std::vector<int>> row = {};
        for (int x = 0; x < width; x++) {
            std::vector<int> cell = {1, 2, 3, 4, 5, 6, 7, 8, 9};
            row.push_back(cell);
        }
        result.push_back(row);
    }

    // result[row][column]
    // result[y][x]
    if (true) {
        // Wikipedia's example sudoku:
        result[0][0] = {5}; result[0][1] = {3}; result[1][0] = {6}; result[0][4] = {7}; result[2][1] = {9};
        result[2][2] = {8}; result[1][3] = {1}; result[1][4] = {9}; result[1][5] = {5}; result[2][7] = {6};
        result[3][0] = {8}; result[4][0] = {4}; result[5][0] = {7}; result[3][8] = {3}; result[4][8] = {1};
        result[5][8] = {6}; result[3][4] = {6}; result[4][5] = {3}; result[4][3] = {8}; result[5][4] = {2}; 
        result[6][1] = {6}; result[6][6] = {2}; result[6][7] = {8}; result[7][8] = {5}; result[8][8] = {9};
        result[8][7] = {7}; result[7][3] = {4}; result[7][4] = {1}; result[8][4] = {8}; result[7][5] = {9};
    }

    if (false) {
        // 17 Hints (min) example#1 from https://web.archive.org/web/20061126162713/http://www.csse.uwa.edu.au/~gordon/sudokumin.php
        result[0][7] = {1};
        result[1][0] = {4};
        result[2][1] = {2};
        result[3][4] = {5};
        result[3][6] = {4};
        result[3][8] = {7};
        result[4][2] = {8};
        result[4][6] = {3};
        result[5][2] = {1};
        result[5][4] = {9};
        result[6][0] = {3};
        result[6][3] = {4};
        result[6][6] = {2};
        result[7][1] = {5};
        result[7][3] = {1};
        result[8][3] = {8};
        result[8][5] = {6};
    }

    return result;
}

void printBoard(std::vector<std::vector<std::vector<int>>> board) {
    // std::cout << "Count: " << sum(board) << ":\n";
    for (int i = 0; i < board.size(); i++) {
        std::vector<std::vector<int>> row = board[i];
        if (i % 3 == 0 && i > 0) {
            std::cout << "------+-------+-------          ------+-------+-------\n";
        }
        for (int j = 0; j < row.size(); j++) {
            std::vector<int> cell = row[j];
            if (j % 3 == 0 && j > 0) {
                std::cout << "| ";
            }
            if (cell.size() == 1 && cell[0] != 0) {
                std::cout << cell[0] << " ";
            } else {
                std::cout << "  ";
            } 
        }
        std::cout << "          ";
        for (int j = 0; j < row.size(); j++) {
            std::vector<int> cell = row[j];
            if (j % 3 == 0 && j > 0) {
                std::cout << "| ";
            }
            std::cout << cell.size() << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

std::vector<std::vector<std::vector<int>>> solve1(std::vector<std::vector<std::vector<int>>> board) {
    // Restrict all those in the same row / column.
    for (int i = 0; i < board.size(); i++) {
        std::vector<std::vector<int>> row = board[i];
        for (int j = 0; j < row.size(); j++) {
            std::vector<int> cell = row[j];
            if (cell.size() == 1) {
                board = restrictRow(board, i, cell[0]);
                board = restrictColumn(board, j, cell[0]);
            }
        }
    }
    std::cout << "Restricted rows and columns; ";
    // printBoard(board);
    
    // Restrict squares.
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            std::vector<int> cell = board[i][j];
            if (cell.size() == 1) {
                board = restrictSquare(board, i / 3, j / 3, cell[0]);
            }
        }
    }
    std::cout << "Restricted squares; ";
    // printBoard(board);

    return board;

    // Fill almost-full rows / coulmns (1 digit missing).

    
}

std::vector<std::vector<std::vector<int>>> restrictRow(std::vector<std::vector<std::vector<int>>> board, int index, int digit) {
    for (int j = 0; j < board[index].size(); j++) {
        std::vector<int> cell = board[index][j];
        if (cell.size() == 1) {
            continue;
        }
        // std::cout << "Removing value " << digit << " from position (" << index << ", " << j << "). ";
        std::vector<int> newCell = {};
        for (int x : cell) {
            if (x != digit) {
                newCell.push_back(x);
            }
        }
        /*std::cout << "Removing value " << digit << " from position (" << index << ", " << j << "). ";
        for (int x : newCell) {
            std::cout << x << ",";
        }
        std::cout << "\n";*/
        board[index][j] = newCell;
    }
    return board;
}

std::vector<std::vector<std::vector<int>>> restrictColumn(std::vector<std::vector<std::vector<int>>> board, int index, int digit) {
    for (int i = 0; i < board[0].size(); i++) {
        std::vector<int> cell = board[i][index];
        if (cell.size() == 1) {
            continue;
        }
        std::vector<int> newCell = {};
        for (int x : cell) {
            if (x != digit) {
                newCell.push_back(x);
            }
        }
        board[i][index] = newCell;
    }
    return board;
}


std::vector<std::vector<std::vector<int>>> restrictSquare(std::vector<std::vector<std::vector<int>>> board, int x, int y, int value) {
    // std::cout << "Restrict square (" << x << ", " << y << ") from " << value << " at: ";
    for (int i = x * 3; i < x * 3 + 3; i++) {
        for (int j = y * 3; j < y * 3 + 3; j++) {
            std::vector<int> cell = board[i][j];
            if (cell.size() == 1) continue;
            // std::cout << "(" << i << ", " << j << ") ";
            std::vector<int> newCell = {};
            for (int x : cell) {
                if (x != value) {
                    newCell.push_back(x);
                }
            }
            board[i][j] = newCell;
        }
    }
    // std::cout << "\n";
    return board;
}

void printVector(std::vector<std::vector<std::vector<int>>> vec) {
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[i].size(); j++) {
            std::cout << "{ ";
            for (int k = 0; k < vec[i][j].size() - 1; k++) {
                std::cout << vec[i][j][k] << ", ";
            }
            std::cout << vec[i][j][vec[i][j].size() - 1] << " },\n";
        }
        std::cout << "\n\n\n";
    }
}

int sum(std::vector<std::vector<std::vector<int>>> board) {
    int count = 0;
    for (int i = 0; i < board.size(); i++) {
        std::vector<std::vector<int>> row = board[i];
        for (int j = 0; j < row.size(); j++) {
            std::vector<int> cell = row[j];
            count += cell.size();
        }
    }
    return count;
}
