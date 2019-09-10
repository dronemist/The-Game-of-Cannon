#include <iostream>
#include "cannon.h"
using namespace std;

Cannon::Cannon(Position startPosition, Position endPosition, Colour colour) {
    this->startPoint = startPosition;
    this->endPoint = endPosition;
    this->colour = colour;
}

PieceType Cannon::getType() {
    return PieceType::cannon;
}