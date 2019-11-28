#include <iostream>
#include "position.h"

using namespace std;

Position::Position(int x, int y) {
    this->x = x;
    this->y = y;
}

// Default constructor
Position::Position() {
    this->x = 0;
    this->y = 0;
}