//
// Created by heeve on 2020-03-08.
//

#include <vector>
#include <iostream>
#include "grid.h"
#include "move.cpp"

#define NUM_CELLS 3


class Grid {
    Move *grid[NUM_CELLS][NUM_CELLS]{};
    bool finished = false;
    int numMoves = 0;
public:

    Grid() {
        for (auto &row : grid) {
            for (auto &col : row) {
                col = nullptr;
            }
        }
    }

    ~Grid() {
        for (auto &row: grid) {
            for (auto &col: row) {
                delete col;
            }
        }
    }

    bool makeMove(int x, int y) {
        if (x < 0 || x > 2 || y < 0 || y > 2 || grid[x][y] != nullptr) {
            std::cout << "Wrong move. Please reenter\n";
            return false;
        }
        Move *newMove;
        if (numMoves % 2 == 0) {
            newMove = new Cross(x, y);
        } else {
            newMove = new Zero(x, y);
        }
        grid[newMove->getX()][newMove->getY()] = newMove;
        isFinished(newMove);
        ++numMoves;
        return true;
    }

    void isFinished(Move *newMove) {
        int countSame = 0;

        // Check column
        for (auto &row : grid) {
            if (row[newMove->getY()] != nullptr && newMove->sameType(row[newMove->getY()])) {
                countSame++;
            } else {
                break;
            }
        }
        if (countSame == NUM_CELLS) {
            finished = true;
            return;
        }
        countSame = 0;

        // Check row
        for (int col = 0; col < NUM_CELLS; ++col) {
            if (grid[newMove->getX()][col] != nullptr && newMove->sameType(grid[newMove->getX()][col])) {
                countSame++;
            } else {
                break;
            }
        }
        if (countSame == NUM_CELLS) {
            finished = true;
            return;
        }
        countSame = 0;

        if ((newMove->getX() + newMove->getY()) % 2 == 1)
            return;  // if move is not placed in diagonal - don't check diagonals


        // Check diagonals

        for (int diag = 0; diag < NUM_CELLS; ++diag) {
            if (grid[diag][diag] != nullptr && newMove->sameType(grid[diag][diag])) {
                countSame++;
            } else {
                break;
            }
        }
        if (countSame == NUM_CELLS) {
            finished = true;
            return;
        }
        countSame = 0;
        for (int diag = 0; diag < NUM_CELLS; ++diag) {
            if (grid[diag][2 - diag] != nullptr && newMove->sameType(grid[diag][2 - diag])) {
                countSame++;
            } else {
                break;
            }
        }
        if (countSame == NUM_CELLS) {
            finished = true;
            return;
        }
    }

    bool getFinished() {
        return finished;
    }

    void printGrid() {
        for (auto &row : grid) {
            for (auto &col : row) {
                if (col == nullptr) {
                    std::cout << " _ ";
                } else {
                    std::cout << col->toString();
                }
            }
            std::cout << std::endl;
        }
    }

    std::vector<std::pair<int, int>> getFreeMoves() {
        std::vector<std::pair<int, int>> free;
        for (int row = 0; row < NUM_CELLS; ++row) {
            for (int col = 0; col < NUM_CELLS; ++col) {
                if (grid[row][col] == nullptr) {
                    free.emplace_back(row, col);
                }
            }
        }
        return free;
    }


};





















