#include <iostream>
#include "board.h"
#define loop(i, start, end) for(int i = start; i < end; i++)
using namespace std;


Board::Board(int rows, int columns) {
    this->columns = columns;
    this->rows = rows;
    // Initialising as null
    this->cannonBoard = vector<vector<Piece*>> (rows, vector<Piece*>(columns, nullptr));
    vector<Position> temp_list = {Position(0,0)};
    temp_list.pop_back();
    this->positionsOfSoldiersOnBoard.push_back(temp_list);
    this->positionsOfSoldiersOnBoard.push_back(temp_list);
    // cout<<"Initialised"<<endl;
    // filling the white pieces
    loop(j, 0, columns) {
        if(j % 2 == 0) {
            Townhall *townhall = new Townhall(Position(j, 0), Colour::white);
            this->cannonBoard[0][j] = townhall;

        } else {
            Soldier *soldier = new Soldier(Colour::white);
            this->cannonBoard[0][j] = soldier;
            Soldier *soldier2 = new Soldier(Colour::white);
            this->cannonBoard[1][j] = soldier2;
            Soldier *soldier3 = new Soldier(Colour::white);
            this->cannonBoard[2][j] = soldier3;

            // Inserting these soldier positions into list of soldiers positions
            this->positionsOfSoldiersOnBoard[1].push_back(Position(j, 0));
            this->positionsOfSoldiersOnBoard[1].push_back(Position(j, 1));
            this->positionsOfSoldiersOnBoard[1].push_back(Position(j, 2));
        }
    }
    // filling the black pieces
    loop(j, 0, columns) {
        int y = rows - 1;
        if(j % 2 == 1) {
            Townhall *townhall = new Townhall(Position(j, y), Colour::black);
            this->cannonBoard[y][j] = townhall;
        } else {
            Soldier *soldier = new Soldier(Colour::black);
            this->cannonBoard[y][j] = soldier;
            Soldier *soldier2 = new Soldier(Colour::black);
            this->cannonBoard[y - 1][j] = soldier2;
            Soldier *soldier3 = new Soldier(Colour::black);
            this->cannonBoard[y - 2][j] = soldier3;

            // Inserting these soldier positions into list of soldier positions
            this->positionsOfSoldiersOnBoard[0].push_back(Position(j, y));
            this->positionsOfSoldiersOnBoard[0].push_back(Position(j, y - 1));
            this->positionsOfSoldiersOnBoard[0].push_back(Position(j, y - 2));
        }
    }
}

void Board::printBoard() {
    loop(i, 0, this->rows) {
        loop(j, 0, this->columns) {
            if(this->cannonBoard[i][j] == nullptr) {
                cout<<"0 ";
            } else {
                if(this->cannonBoard[i][j]->getType() == PieceType::soldier)
                    if(this->cannonBoard[i][j]->getColour() == Colour::black)
                        cout<<"1 ";
                    else
                        cout<<"3 ";
                else if(this->cannonBoard[i][j]->getType() == PieceType::townhall)
                    if(this->cannonBoard[i][j]->getColour() == Colour::black)
                        cout<<"2 ";
                    else
                        cout<<"4 ";
            }
        }
        cout<<endl;
    }
}

int Board::getRows() {
    return this->rows;
}

int Board::getColumns() {
    return this->columns;
}

int Board::numberOfBlackTownhalls(){
  int count = 0;

  for(int j = 1; j < this->columns; j += 2) {
    if(this->cannonBoard[this->rows - 1][j] != nullptr
    && this->cannonBoard[this->rows - 1][j]->getType() == PieceType::townhall){
      ++count;
    }
  }

  return count;
}

int Board::numberOfWhiteTownhalls(){
  int count = 0;

  for(int j = 0; j < this->columns; j += 2) {
    if(this->cannonBoard[0][j] != nullptr &&
    this->cannonBoard[0][j]->getType() == PieceType::townhall){
      ++count;
    }
  }

  return count;
}

bool isAllySoldierPresent(Piece* ptr, int soldierColor){
  if(ptr != nullptr && int(ptr->getColour()) == soldierColor && ptr->getType() == PieceType::soldier)
    return true;
  return false;
}


int Board::numberOfCannonsOnBoard(vector< vector<Position> > &positionsOfSoldiersOnBoard, int pieceColour){  // Piece color 0 for black, 1 for white

  int numRows = this->getRows();
  int numCols = this->getColumns();
  int count = 0;



  for(vector<Position>::iterator it = positionsOfSoldiersOnBoard[pieceColour].begin(); it != positionsOfSoldiersOnBoard[pieceColour].end(); ++it){

    int x = it-> x;
    int y = it-> y;

    bool isLeftMostOfHorizontalCannon = ((x + 2) < numCols) && isAllySoldierPresent(this->cannonBoard[y][x+1], pieceColour) && isAllySoldierPresent(this->cannonBoard[y][x+2], pieceColour);
    bool isTopLeftMostOfCannon = ((x+2) < numCols) && ((y+2) < numRows) && isAllySoldierPresent(this->cannonBoard[y+1][x+1], pieceColour) && isAllySoldierPresent(this->cannonBoard[y+2][x+2], pieceColour);
    bool isTopMostOfVerticalCannon = ((y+2) < numRows) && isAllySoldierPresent(this->cannonBoard[y+1][x], pieceColour) && isAllySoldierPresent(this->cannonBoard[y+2][x], pieceColour);
    bool isTopRightMostOfCannon = ((x-2) >= 0) && ((y+2) < numRows) && isAllySoldierPresent(this->cannonBoard[y+1][x-1], pieceColour) && isAllySoldierPresent(this->cannonBoard[y + 2][x - 2], pieceColour);

    count += isLeftMostOfHorizontalCannon + isTopLeftMostOfCannon + isTopMostOfVerticalCannon + isTopRightMostOfCannon;

  }

  return count;

}
