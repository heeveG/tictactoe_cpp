#include <iostream>
#include <functional>
#include "player.cpp"


int main() {

    Grid grid = Grid();
    std::vector<Players *> players;
    std::vector<std::string> input{2};

    std::cout << "First player: ";
    std::cin >> input[0];

    std::cout << "Second player: ";
    std::cin >> input[1];

    for (int i = 0; i < 2; ++i) {
        if (input[i] == "h") {
            players.push_back(new Human(&grid, (i + 1)));
        } else if (input[i] == "lvl1") {
            players.push_back(new Robot(&grid, (i + 1)));
        } else if (input[i] == "lvl2") {
            players.push_back(new Robot2(&grid, (i + 1)));
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
