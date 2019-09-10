#include <iostream>
#include "townhall.h"

using namespace std;

Townhall::Townhall(Position position, Colour colour) {
    this->colour = colour;
    this->position = position;
}

PieceType Townhall::getType() {
    return PieceType::townhall;
}
