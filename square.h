#include <iostream>
#ifndef SQUARE_H

class Square {
    private:
        int xLocation;
        int yLocation;
        int value;

    public:
        Square(int x, int y, int v);
        ~Square();
        void draw();
}
#endif