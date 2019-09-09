#include <iostream>
#include "soldier.h"

using namespace std;

Soldier::Soldier(Position position, Colour colour) {
    this->colour = colour;
    this->position = position;
}

PieceType Soldier::getType() {
    return PieceType::soldier;
}