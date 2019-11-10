#include <iostream>
#include "townhall.h"

using namespace std;

Townhall::Townhall(Colour colour) {
    this->colour = colour;
}

PieceType Townhall::getType() {
    return PieceType::townhall;
}
