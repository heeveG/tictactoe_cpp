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
    std::string name{""};
    Grid &grid;
public:


    Players(Grid *grid, std::string name) : grid(*grid), name(std::move(name)) {
    }

    virtual void move() {
    }

    bool won() {

        return grid.getFinished();
    }

    std::string getWinner() {
        return name;
    }

};


class Human : public Players {
public:

    Human(Grid *grid, std::string name) : Players(grid, std::move(name)) {}

    void move() override {
        int x = 0, y = 0;
        do {
            std::cout << name << " : Enter x: \n";
            std::cin >> x;
            std::cout << name << " : Enter y: \n";
            std::cin >> y;
        } while (!grid.makeMove(x, y));
        grid.printGrid();
    }

};

class Robot : public Players {

public:
    Robot(Grid *grid, std::string name) : Players(grid, std::move(name)) {}

    std::pair<int, int> randomMove() {
        std::vector<std::pair<int, int>> free = grid.getFreeMoves();
        std::random_device r;
        std::default_random_engine e1(r());
        std::uniform_int_distribution<int> randInx(0, free.size() - 1);
        return free[randInx(e1)];
    }

    void move() override {
        int x, y;
        std::pair<int, int> pair = randomMove();
        x = pair.first;
        y = pair.second;
        grid.makeMove(x, y);
        grid.printGrid();
    }

};