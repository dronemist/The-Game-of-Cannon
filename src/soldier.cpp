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

Soldier::Soldier(Colour colour) {
    this->colour = colour;
}

PieceType Soldier::getType() {
    return PieceType::soldier;
}

void Soldier::getAllowedMoves(Board &currentBoard, Position* position, vector<string> &answer) {
    int x = position->x;
    int y = position->y;
    int blackWhiteFactor = this->colour == Colour::black ? 1 : -1;
    // tells if the piece can retreat
    bool canRetreat = false;
    if((y > 0 && this->colour == Colour::black)
    || (y < currentBoard.getRows() - 1 && this->colour == Colour::white)) {
        if(this->canMoveToPosition(currentBoard.cannonBoard[y - blackWhiteFactor][x])) {
            answer.push_back(moveEncoding(x, y, x, y - blackWhiteFactor));
        }
        if(this->isOpponentSoldierPresent(currentBoard.cannonBoard[y - blackWhiteFactor][x])) {
                canRetreat = true;
        }
        if(x < currentBoard.getColumns() - 1
        && this->canMoveToPosition(currentBoard.cannonBoard[y - blackWhiteFactor][x + 1])) {
            answer.push_back(moveEncoding(x, y, x + 1, y - blackWhiteFactor));
            if(this->isOpponentSoldierPresent(currentBoard.cannonBoard[y - blackWhiteFactor][x + 1])) {
                canRetreat = true;
            }
        }
        if(x > 0 && this->canMoveToPosition(currentBoard.cannonBoard[y - blackWhiteFactor][x - 1])) {
            answer.push_back(moveEncoding(x, y, x - 1, y - blackWhiteFactor));
            if(this->isOpponentSoldierPresent(currentBoard.cannonBoard[y - blackWhiteFactor][x - 1])) {
                canRetreat = true;
            }
        }
    }
    // can move to the right
    bool canMoveRight = (x < currentBoard.getColumns() - 1)
    && this->isOpponentPresent(currentBoard.cannonBoard[y][x + 1]);

    if(canMoveRight) {
        answer.push_back(moveEncoding(x, y, x + 1, y));
        if(currentBoard.cannonBoard[y][x + 1]->getType() == PieceType::soldier) {
          canRetreat = true;
        }
    }

    // can move to the left
    bool canMoveLeft = (x > 0)
    && this->isOpponentPresent(currentBoard.cannonBoard[y][x - 1]);

    if(canMoveLeft) {
        answer.push_back(moveEncoding(x, y, x - 1, y));
        if(currentBoard.cannonBoard[y][x - 1]->getType() == PieceType::soldier) {
          canRetreat = true;
        }
    }

    // If the piece can retreat
    if(canRetreat) {
        if((y < currentBoard.getRows() - 2 && this->colour == Colour::black)
        || (y > 1 && this->colour == Colour::white)) {
            if(this->canMoveToPosition(currentBoard.cannonBoard[y + 2 * blackWhiteFactor][x]))
            answer.push_back(moveEncoding(x, y, x, y + 2 * blackWhiteFactor));
            if(x > 1
            && this->canMoveToPosition(currentBoard.cannonBoard[y + 2 * blackWhiteFactor][x - 2])) {
                answer.push_back(moveEncoding(x, y, x - 2, y + 2 * blackWhiteFactor));
            }
            if(x < currentBoard.getColumns() - 2
             && this->canMoveToPosition(currentBoard.cannonBoard[y + 2 * blackWhiteFactor][x + 2])) {
                answer.push_back(moveEncoding(x, y, x + 2, y + 2 * blackWhiteFactor));
            }
        }
    }

    vector<string> cannonMoves;
    getAllowedCannonMoves(currentBoard, position, cannonMoves);
    answer.insert(answer.end(), cannonMoves.begin(), cannonMoves.end());
}


/// This returns all the cannon moves in the current Board
void Soldier::getAllowedCannonMoves(Board &currentBoard, Position* position, vector<string> &answer){

  int x = position->x;
  int y = position->y;

  int numRows = currentBoard.getRows();
  int numCols = currentBoard.getColumns();

  // Checking for the four orientations
  bool isLeftMostOfHorizontalCannon = ((x + 2) < numCols) && isAllySoldierPresent(currentBoard.cannonBoard[y][x+1]) && isAllySoldierPresent(currentBoard.cannonBoard[y][x+2]);
  bool isTopLeftMostOfCannon = ((x+2) < numCols) && ((y+2) < numRows) && isAllySoldierPresent(currentBoard.cannonBoard[y+1][x+1]) && isAllySoldierPresent(currentBoard.cannonBoard[y+2][x+2]);
  bool isTopMostOfVerticalCannon = ((y+2) < numRows) && isAllySoldierPresent(currentBoard.cannonBoard[y+1][x]) && isAllySoldierPresent(currentBoard.cannonBoard[y+2][x]);
  bool isTopRightMostOfCannon = ((x-2) >= 0) && ((y+2) < numRows) && isAllySoldierPresent(currentBoard.cannonBoard[y+1][x-1]) && isAllySoldierPresent(currentBoard.cannonBoard[y + 2][x - 2]);



  if(isLeftMostOfHorizontalCannon){
    // First checking for movement of cannon
    if((x + 3) < numCols && isPositionEmpty(currentBoard.cannonBoard[y][x+3])){
      answer.push_back(moveEncoding(x, y, x + 3, y));
    }

    if((x - 1) >= 0 && isPositionEmpty(currentBoard.cannonBoard[y][x-1])){
      answer.push_back(moveEncoding(x + 2, y, x - 1, y));
    }

    // Checking for closer CannonShot in right direction, can do blank shot also
    if((x + 4) < numCols && isPositionEmpty(currentBoard.cannonBoard[y][x+3]) && canMoveToPosition(currentBoard.cannonBoard[y][x+4])){
      answer.push_back(cannonShotEncoding(x, y, x + 4, y));
    }

    // Further shot in right direction
    // NOTE: Can a cannon shoot at farther end if soldier in the line?
    if((x + 5) < numCols && isPositionEmpty(currentBoard.cannonBoard[y][x+3]) && canMoveToPosition(currentBoard.cannonBoard[y][x+5])){
      answer.push_back(cannonShotEncoding(x, y, x + 5, y));
    }

    // Checking for shooting in Left, closer shot
    if((x - 2) >= 0 && isPositionEmpty(currentBoard.cannonBoard[y][x-1]) && canMoveToPosition(currentBoard.cannonBoard[y][x-2])){
      answer.push_back(cannonShotEncoding(x, y, x - 2, y));
    }

    // Further shot in left direction
    // NOTE: Can a cannon shoot at farther end if soldier in the line?
    if((x - 3) >= 0 && isPositionEmpty(currentBoard.cannonBoard[y][x-1]) && canMoveToPosition(currentBoard.cannonBoard[y][x-3])){
      answer.push_back(cannonShotEncoding(x, y, x - 3, y));
    }
  }


  if(isTopMostOfVerticalCannon){
    // First checking for movement of cannon
    if((y + 3) < numRows && isPositionEmpty(currentBoard.cannonBoard[y+3][x])){
      answer.push_back(moveEncoding(x, y, x, y + 3));
    }

    if((y - 1) >= 0 && isPositionEmpty(currentBoard.cannonBoard[y-1][x])){
      answer.push_back(moveEncoding(x, y + 2, x, y - 1));
    }

    // Checking for closer CannonShot in down direction, can do blank shot also
    if((y + 4) < numRows && isPositionEmpty(currentBoard.cannonBoard[y+3][x]) && canMoveToPosition(currentBoard.cannonBoard[y+4][x])){
      answer.push_back(cannonShotEncoding(x, y, x, y + 4));
    }

    // Further shot in down direction
    // NOTE: Can a cannon shoot at farther end if soldier in the line?
    if((y + 5) < numRows && isPositionEmpty(currentBoard.cannonBoard[y+3][x]) && canMoveToPosition(currentBoard.cannonBoard[y+5][x])){
      answer.push_back(cannonShotEncoding(x, y, x, y + 5));
    }

    // Checking for shooting upwards, closer shot
    if((y - 2) >= 0 && isPositionEmpty(currentBoard.cannonBoard[y-1][x]) && canMoveToPosition(currentBoard.cannonBoard[y-2][x])){
      answer.push_back(cannonShotEncoding(x, y, x, y - 2));
    }

    // Further shot in upper direction
    // NOTE: Can a cannon shoot at farther end if soldier in the line?
    if((y - 3) >= 0 && isPositionEmpty(currentBoard.cannonBoard[y-1][x]) && canMoveToPosition(currentBoard.cannonBoard[y-3][x])){
      answer.push_back(cannonShotEncoding(x, y, x, y - 3));
    }
  }



  if(isTopLeftMostOfCannon){
    // First checking for movement of cannon
    if((x + 3) < numCols && (y + 3) < numRows && isPositionEmpty(currentBoard.cannonBoard[y+3][x+3])){
      answer.push_back(moveEncoding(x, y, x + 3, y + 3));
    }

    if((x - 1) >= 0 && (y - 1) >= 0 && isPositionEmpty(currentBoard.cannonBoard[y-1][x-1])){
      answer.push_back(moveEncoding(x + 2, y + 2, x - 1, y - 1));
    }

    // Checking for closer CannonShot in down direction, can do blank shot also
    if((x + 4) < numCols && (y + 4) < numRows && isPositionEmpty(currentBoard.cannonBoard[y+3][x+3]) && canMoveToPosition(currentBoard.cannonBoard[y+4][x+4])){
      answer.push_back(cannonShotEncoding(x, y, x + 4, y + 4));
    }

    // Further shot in down direction
    // NOTE: Can a cannon shoot at farther end if soldier in the line?
    if((x + 5) < numCols && (y + 5) < numRows && isPositionEmpty(currentBoard.cannonBoard[y+3][x+3]) && canMoveToPosition(currentBoard.cannonBoard[y+5][x+5])){
      answer.push_back(cannonShotEncoding(x, y, x + 5, y + 5));
    }

    // Checking for shooting upwards, closer shot
    if((x - 2) >= 0 && (y - 2) >= 0 && isPositionEmpty(currentBoard.cannonBoard[y-1][x-1]) && canMoveToPosition(currentBoard.cannonBoard[y-2][x-2])){
      answer.push_back(cannonShotEncoding(x, y, x - 2, y - 2));
    }

    // Further shot in upper direction
    // NOTE: Can a cannon shoot at farther end if soldier in the line?
    if((x - 3) >= 0 && (y - 3) >= 0 && isPositionEmpty(currentBoard.cannonBoard[y-1][x-1]) && canMoveToPosition(currentBoard.cannonBoard[y-3][x-3])){
      answer.push_back(cannonShotEncoding(x, y, x - 3, y - 3));
    }

  }

  if(isTopRightMostOfCannon){
    // First checking for movement of cannon
    if((x - 3) >= 0 && (y + 3) < numRows && isPositionEmpty(currentBoard.cannonBoard[y+3][x-3])){
      answer.push_back(moveEncoding(x, y, x - 3, y + 3));
    }

    if((x + 1) < numCols && (y - 1) >= 0 && isPositionEmpty(currentBoard.cannonBoard[y-1][x+1])){
      answer.push_back(moveEncoding(x - 2, y + 2, x + 1, y - 1));
    }

    // Checking for closer CannonShot in down direction, can do blank shot also
    if((x - 4) >= 0 && (y + 4) < numRows && isPositionEmpty(currentBoard.cannonBoard[y+3][x-3]) && canMoveToPosition(currentBoard.cannonBoard[y+4][x-4])){
      answer.push_back(cannonShotEncoding(x, y, x - 4, y + 4));
    }

    // Further shot in down direction
    // NOTE: Can a cannon shoot at farther end if soldier in the line?
    if((x - 5) >= 0 && (y + 5) < numRows && isPositionEmpty(currentBoard.cannonBoard[y+3][x-3]) && canMoveToPosition(currentBoard.cannonBoard[y+5][x-5])){
      answer.push_back(cannonShotEncoding(x, y, x - 5, y + 5));
    }

    // Checking for shooting upwards, closer shot
    if((x + 2) < numCols && (y - 2) >= 0 && isPositionEmpty(currentBoard.cannonBoard[y-1][x+1]) && canMoveToPosition(currentBoard.cannonBoard[y-2][x+2])){
      answer.push_back(cannonShotEncoding(x, y, x + 2, y - 2));
    }

    // Further shot in upper direction
    // NOTE: Can a cannon shoot at farther end if soldier in the line?
    if((x + 3) < numCols && (y - 3) >= 0 && isPositionEmpty(currentBoard.cannonBoard[y-1][x+1]) && canMoveToPosition(currentBoard.cannonBoard[y-3][x+3])){
      answer.push_back(cannonShotEncoding(x, y, x + 3, y - 3));
    }
  }
}

bool Soldier::isOpponentSoldierPresent(Piece *ptr) {
  if(this->isOpponentPresent(ptr) && ptr->getType() == PieceType::soldier)
    return true;
  return false;
}


/// This function tells if an opponent is present
bool Soldier::isOpponentPresent(Piece *ptr) {
    if(ptr != nullptr && ptr->getColour() != this->colour)
        return true;
    return false;
}

bool Soldier::isAllySoldierPresent(Piece* ptr){
  if(ptr != nullptr && ptr->getColour() == this->colour && ptr->getType() == PieceType::soldier)
    return true;
  return false;
}

bool Soldier::isPositionEmpty(Piece *ptr){
  if(ptr == nullptr)
      return true;
  return false;
}

/// This function tells if soldier can move to ptr
bool Soldier::canMoveToPosition(Piece *ptr) {
    if(ptr == nullptr || this->isOpponentPresent(ptr))
        return true;
    return false;
}

string Soldier::moveEncoding(int initialPositionX, int initialPositionY, int finalPositionX, int finalPositionY){
    return ("S " + intToString(initialPositionX) + " " + intToString(initialPositionY) + " M " + intToString(finalPositionX) + " " + intToString(finalPositionY));
}

string Soldier::cannonShotEncoding(int soldierPositionX, int soldierPositionY, int shotPositionX, int shotPositionY){
    // this solider is doing the cannonshot only
    return ("S " + intToString(soldierPositionX) + " " + intToString(soldierPositionY) + " B " + intToString(shotPositionX) + " " + intToString(shotPositionY));
}
