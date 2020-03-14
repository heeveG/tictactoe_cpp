#include <iostream>
#include <functional>
#include "player.cpp"


int main() {

    Grid grid = Grid();

    std::vector<Players *> players;
    players.reserve(2);
    std::vector<std::string> input{"First", "Second"};
    std::string inp;

    std::cout << "h - human, lvl1 - computer using random, lvl2 -- computer, using binary tree.\n";

    for (int i = 0; i < 2; ++i) {
        std::cout << input[i] + " player: ";
        std::cin >> inp;

        if (inp == "h") {
            players.emplace_back(new Human(&grid, (i + 1)));
        } else if (inp== "lvl1") {
            players.emplace_back(new Robot(&grid, (i + 1)));
        } else if (inp == "lvl2") {
            players.emplace_back(new Robot2(&grid, (i + 1)));
        }
        else{
            std::cout << "Wrong input. Please reenter\n";
            i -= 1;
        }
    }

    int numPlayer = 0;
    while (!players[numPlayer]->won()) {
        players[numPlayer]->move();
        numPlayer = (numPlayer + 1) % 2;
        std::cout << std::endl;
    }
    std::cout << players[0]->getWinner();

    for (auto p: players) {
        delete p;
    }
    players.clear();
    input.clear();
    return 0;
}
