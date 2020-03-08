//
// Created by heeve on 2020-03-08.
//

#include "move.h"

class Move {
    int y;
    int x;
public:

    Move(const int &x_in, const int &y_in) : x(x_in), y(y_in) {}

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    virtual bool sameType(Move *obj) {
        return typeid(*this) == typeid(*obj);
    }

    virtual std::string toString() {}
};

class Zero : public Move {
public:
    Zero(const int &x_in, const int &y_in) : Move(x_in, y_in) {}

    std::string toString() override {
        return " 0 ";
    }

};

class Cross : public Move {

public:
    Cross(const int &x_in, const int &y_in) : Move(x_in, y_in) {}

    std::string toString() override {
        return " X ";
    }

};