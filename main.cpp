#include <iostream>
#include <vector>
#include "functions.h"

int main() {
    std::vector<std::vector<std::vector<int>>> board = getBoard();
    std::cout << "Starting with " << (729 - sum(board)) / 8 << " reveals.\n";
    printBoard(board);
    int i = 1;
    int count = 729;
    while (sum(board) < count) {
        count = sum(board);
        if (count == 81) break;
        board = solve1(board);
        std::cout << "\nSolved #" << i << ".\nCount: " << sum(board) << "\n\n";
        ++i;
    }
    printBoard(board);
    if (sum(board) > 81) {
        std::cout << "Puzzle unsolvable by me. " << sum(board) - 81 << " possible solutions.";
    } else {
        std::cout << "Solved within " << i - 1 << " iterations.";
    }
    // printVector(board);
}

// Read file with unsolved sudoku and convert it to board.
//     Spaceless and spaced formats. Auto-identification. Instructions.
