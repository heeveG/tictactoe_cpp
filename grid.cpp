//
// Created by heeve on 2020-03-08.
//

#include <vector>
#include <iostream>
#include "grid.h"
#include "move.cpp"

#define NUM_CELLS 3

enum Status {
    CROSS_WIN = 1, ZERO_WIN = -1, DRAW = 0
};

class Grid {


    Move *grid[NUM_CELLS][NUM_CELLS]{};
    bool finished = false;
    int numMoves = 0;
    Status status;
public:


    Grid() {
        for (auto &row : grid) {
            for (auto &col : row) {
                col = nullptr;
            }
        }
    }

    Grid(const Grid& other) : finished(other.finished), numMoves(other.numMoves), status(other.status)
    {
        for (int row = 0; row < NUM_CELLS; ++row) {
            for (int col = 0; col < NUM_CELLS; ++col) {
                if (other.grid[row][col] != nullptr) {
                    grid[row][col] = other.grid[row][col]->makeCopy();
                }
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

    bool makeMove(const int &x, const int &y) {
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
        ++numMoves;
        isFinished(newMove);
        return true;
    }

    void isFinished(Move *newMove) {
        int countSame = 0;

        Status potentialWinner = (numMoves % 2 == 0) ? ZERO_WIN : CROSS_WIN;

        // Check column
        for (auto &row : grid) {
            if (row[newMove->getY()] != nullptr && newMove->sameType(row[newMove->getY()])) {
                countSame++;
            } else {
                break;
            }
        }
        if (countSame == NUM_CELLS) {
            setWinner(potentialWinner);
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
            setWinner(potentialWinner);
            return;
        }
        countSame = 0;

        // Check diagonals
        for (int diag = 0; diag < NUM_CELLS; ++diag) {
            if (grid[diag][diag] != nullptr && newMove->sameType(grid[diag][diag])) {
                countSame++;
            } else {
                break;
            }
        }
        if (countSame == NUM_CELLS) {
            setWinner(potentialWinner);
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
            setWinner(potentialWinner);
            return;
        }

        // Check for draw
        if (numMoves == NUM_CELLS * NUM_CELLS) {
            setWinner(DRAW);
            return;
        }
    }

    bool getFinished() {
        return finished;
    }

    void printGrid() {
        for (auto &row : grid) {
            for (auto &col : row) {
                std::cout << "|";
                if (col == nullptr) {
                    std::cout << " _ ";
                } else {
                    std::cout << col->toString();
                }
            }
            std::cout << "|";
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

    void setWinner(Status winner) {
        finished = true;
        status = winner;
    }

    Status getStatus() {
        return status;
    }

};





















