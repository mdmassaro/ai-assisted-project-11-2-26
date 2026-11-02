#include <iostream>

#ifndef SQUARE_H
#define SQUARE_H

class Square {
private:
    int xLocation;
    int yLocation;
    int value;

public:
    Square(int x = 0, int y = 0, int v = 0)
        : xLocation(x), yLocation(y), value(v) {}

    int getXLocation() const { return xLocation; }
    int getYLocation() const { return yLocation; }
    int getValue() const { return value; }
    void setValue(int v) { value = v; }

    void draw() const {
        if (value == 0) {
            std::cout << '.';
        } else {
            std::cout << value;
        }
    }
};

#endif