#include <iostream>
#include <sstream>
#include "soldier.h"

using namespace std;

/// This function converts an integer to a string
string intToString(int k) {
    stringstream ss;  
    ss<<k;  
    string s;  
    ss>>s;
    return s;
}

Soldier::Soldier(Position position, Colour colour) {
    this->colour = colour;
    this->position = position;
}

PieceType Soldier::getType() {
    return PieceType::soldier;
}

vector<string> Soldier::getAllowedMoves(Board &currentBoard) {
    vector<string> answer;
    int x = this->position.x;
    int y = this->position.y;
    int blackWhiteFactor = this->colour == Colour::black ? 1 : -1;
    // tells if the piece can retreat;
    bool canRetreat = false;
    if((y > 0 && this->colour == Colour::black)
    || (y < currentBoard.getRows() - 1 && this->colour == Colour::white)) {
        if(this->canMoveToPosition(currentBoard.cannonBoard[y - blackWhiteFactor][x])) {
            answer.push_back("S " + intToString(x) + " " + intToString(y) + " M " 
            + intToString(x) + " " + intToString(y - blackWhiteFactor));
        }
        if(this->isOpponentPresent(currentBoard.cannonBoard[y - blackWhiteFactor][x])) {
                canRetreat = true;
        }
        if(x < currentBoard.getColumns() - 1 
        && this->canMoveToPosition(currentBoard.cannonBoard[y - blackWhiteFactor][x + 1])) {
            answer.push_back("S " + intToString(x) + " " + intToString(y) + " M " 
            + intToString(x + 1) + " " + intToString(y - blackWhiteFactor));
            if(this->isOpponentPresent(currentBoard.cannonBoard[y - blackWhiteFactor][x + 1])) {
                canRetreat = true;
            }
        }
        if(x > 0 && this->canMoveToPosition(currentBoard.cannonBoard[y - blackWhiteFactor][x - 1])) {
            answer.push_back("S " + intToString(x) + " " + intToString(y) + " M " 
            + intToString(x - 1) + " " + intToString(y - blackWhiteFactor));
            if(this->isOpponentPresent(currentBoard.cannonBoard[y - blackWhiteFactor][x - 1])) {
                canRetreat = true;
            }
        }
    }
    // can move to the right
    bool canMoveRight = (x < currentBoard.getColumns() - 1) 
    && this->isOpponentPresent(currentBoard.cannonBoard[y][x + 1]);

    if(canMoveRight) {
        answer.push_back("S " + intToString(x) + " " + intToString(y) + " M " 
        + intToString(x + 1) + " " + intToString(y));
        canRetreat = true;
    }

    // can move to the left
    bool canMoveLeft = (x > 0) 
    && this->isOpponentPresent(currentBoard.cannonBoard[y][x - 1]);

    if(canMoveLeft) {
        answer.push_back("S " + intToString(x) + " " + intToString(y) + " M " 
        + intToString(x - 1) + " " + intToString(y));
        canRetreat = true;
    }

    // If the piece can retreat
    if(canRetreat) {
        if((y < currentBoard.getRows() - 2 && this->colour == Colour::black)
        || (y > 1 && this->colour == Colour::white)) {
            if(this->canMoveToPosition(currentBoard.cannonBoard[y + 2 * blackWhiteFactor][x]))
            answer.push_back("S " + intToString(x) + " " + intToString(y) + " M " 
            + intToString(x) + " " + intToString(y + 2 * blackWhiteFactor));
            if(x > 1 
            && this->canMoveToPosition(currentBoard.cannonBoard[y + 2 * blackWhiteFactor][x - 2])) {
                answer.push_back("S " + intToString(x) + " " + intToString(y) + " M " 
                + intToString(x - 2) + " " + intToString(y + 2 * blackWhiteFactor));
            }
            if(x < currentBoard.getColumns() - 2
             && this->canMoveToPosition(currentBoard.cannonBoard[y + 2 * blackWhiteFactor][x + 2])) {
                answer.push_back("S " + intToString(x) + " " + intToString(y) + " M " 
                + intToString(x + 2) + " " + intToString(y + 2 * blackWhiteFactor));
            }
        }
    }
    return answer;
}
/// This function tells if an opponent is present
bool Soldier::isOpponentPresent(Piece *ptr) {
    if(ptr != nullptr && ptr->getColour() != this->colour)
        return true;
    return false;    
}

/// This function tells if soldier can move to ptr
bool Soldier::canMoveToPosition(Piece *ptr) {
    if(ptr == nullptr || this->isOpponentPresent(ptr))
        return true;
    return false;    
}