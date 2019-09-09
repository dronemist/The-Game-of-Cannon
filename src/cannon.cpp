#include <iostream>
#include "cannon.h"
using namespace std;

Cannon::Cannon(Position startPosition, Position endPosition, Colour colour) {
    this->startPoint = startPoint;
    this->endPoint = endPoint;
    this->colour = colour;
}

PieceType Cannon::getType() {
    return PieceType::cannon;
}