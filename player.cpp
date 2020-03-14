//
// Created by heeve on 2020-03-08.
//

#include "player.h"

#include <utility>
#include <functional>
#include <random>
#include "grid.cpp"

class Players {

protected:
    int id;
    Grid &grid;
public:


    Players(Grid *grid, int id) : grid(*grid), id(id) {
    }

    virtual void move() {
    }

    bool won() {
        return grid.getFinished();
    }

    std::string getWinner() {
        if (won()) {
            if (grid.getStatus() == CROSS_WIN) {
                return "Player 1 won\n";
            } else if (grid.getStatus() == ZERO_WIN) {
                return "Player 2 won\n";
            } else {
                return "It's a draw\n";
            }
        }
        return "Game goes on\n";
    }

};


class Human : public Players {
public:

    Human(Grid *grid, int id) : Players(grid, id) {}

    void move() override {
        int x = 0, y = 0;
        do {
            std::cout << "Player " + std::to_string(id) << " : Enter x: \n";
            std::cin >> x;
            std::cout << "Player " + std::to_string(id) << " : Enter y: \n";
            std::cin >> y;
        } while (!grid.makeMove(x, y));
        grid.printGrid();
    }

};

class Robot : public Players {

public:
    Robot(Grid *grid, int id) : Players(grid, id) {}

    static std::pair<int, int> randomMove(std::vector<std::pair<int, int>> free) {
        std::random_device r;
        std::default_random_engine e1(r());
        std::uniform_int_distribution<int> randInx(0, free.size() - 1);
        return free[randInx(e1)];
    }

    void move() override {
        int x, y;
        std::pair<int, int> pair = randomMove(grid.getFreeMoves());
        x = pair.first;
        y = pair.second;
        grid.makeMove(x, y);
        grid.printGrid();
    }

};

class Robot2 : public Robot {
public:
    Robot2(Grid *grid, int id) : Robot(grid, std::move(id)) {}

    int recurse(Grid &grid_rec) {
        if (!grid_rec.getFinished()) {
            Grid g1 = grid_rec;
            Grid g2 = grid_rec;
            int x, y;
            std::pair<int, int> pair = randomMove(g1.getFreeMoves());
            x = pair.first;
            y = pair.second;
            g1.makeMove(x, y);
            pair = randomMove(g2.getFreeMoves());
            x = pair.first;
            y = pair.second;
            g2.makeMove(x, y);
            return recurse(g1) + recurse(g2);
        }
        int res = grid_rec.getStatus() * pow(-1, id + 1);
        return res;
    }

    void move() override {
        int x1, x2, y1, y2;
        Grid g1 = grid;
        Grid g2 = grid;

        std::pair<int, int> pair = randomMove(grid.getFreeMoves());
        x1 = pair.first;
        y1 = pair.second;
        pair = randomMove(grid.getFreeMoves());
        x2 = pair.first;
        y2 = pair.second;

        g1.makeMove(x1, y1);
        g2.makeMove(x2, y2);

        if (recurse(g1) > recurse(g2)) {
            grid.makeMove(x1, y1);
        } else {
            grid.makeMove(x2, y2);
        }
        grid.printGrid();

    }
};