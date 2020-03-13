//
// Created by heeve on 2020-03-08.
//

#include "move.h"

class Move {
protected:
    int x;
    int y;
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

    virtual Move *makeCopy() {}

};

class Zero : public Move {
public:
    Zero(const int &x_in, const int &y_in) : Move(x_in, y_in) {}

    std::string toString() override {
        return " 0 ";
    }

    Move *makeCopy() override {
        Move *newMove = new Zero(x, y);
        return newMove;
    }

};

class Cross : public Move {

public:
    Cross(const int &x_in, const int &y_in) : Move(x_in, y_in) {}

    std::string toString() override {
        return " X ";
    }

    Move *makeCopy() override {
        Move *newMove = new Cross(x, y);
        return newMove;
    }


};