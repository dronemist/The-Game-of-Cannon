#include <iostream>
#include "board.h"
#define loop(i, start, end) for(int i = start; i < end; i++)
using namespace std;

Soldier *whiteSoldier = new Soldier(Colour::white);
Soldier *blackSoldier = new Soldier(Colour::black);
Townhall *whiteTownHall = new Townhall(Colour::white);
Townhall *blackTownHall = new Townhall(Colour::black);

Board::Board(int rows, int columns) {
    this->columns = columns;
    this->rows = rows;
    // Initialising as null
    this->cannonBoard = vector<vector<Piece*>> (rows, vector<Piece*>(columns, nullptr));
    vector<Position> temp_list = {Position(0,0)};
    temp_list.pop_back();
    this->positionsOfSoldiersOnBoard.push_back(temp_list);
    this->positionsOfSoldiersOnBoard.push_back(temp_list);
    // filling the white pieces
    loop(j, 0, columns) {
        if(j % 2 == 0) {
            Townhall *townhall = whiteTownHall;
            this->cannonBoard[0][j] = townhall;

        } else {
            Soldier *soldier = whiteSoldier;
            this->cannonBoard[0][j] = soldier;
            Soldier *soldier2 = whiteSoldier;
            this->cannonBoard[1][j] = soldier2;
            Soldier *soldier3 = whiteSoldier;
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
            Townhall *townhall =blackTownHall;
            this->cannonBoard[y][j] = townhall;
        } else {
            Soldier *soldier = blackSoldier;
            this->cannonBoard[y][j] = soldier;
            Soldier *soldier2 = blackSoldier;
            this->cannonBoard[y - 1][j] = soldier2;
            Soldier *soldier3 = blackSoldier;
            this->cannonBoard[y - 2][j] = soldier3;

            // Inserting these soldier positions into list of soldier positions
            this->positionsOfSoldiersOnBoard[0].push_back(Position(j, y));
            this->positionsOfSoldiersOnBoard[0].push_back(Position(j, y - 1));
            this->positionsOfSoldiersOnBoard[0].push_back(Position(j, y - 2));
        }
    }
}


void Board::freeMemory() {
    
    cout<<"Destructing"<<endl;
    loop(i, 0, positionsOfSoldiersOnBoard[0].size()){
        Position temp = positionsOfSoldiersOnBoard[0][i];
        // cout<<"Here"<<endl;
        if (this->cannonBoard[temp.y][temp.x] != nullptr){
            delete this->cannonBoard[temp.y][temp.x];
            this->cannonBoard[temp.y][temp.x] = nullptr;
        }
    }

    // cout<<"There"<<endl;
    

    loop(i, 0, positionsOfSoldiersOnBoard[1].size()){
        Position temp = positionsOfSoldiersOnBoard[1][i];
        if (this->cannonBoard[temp.y][temp.x] != nullptr){
            delete this->cannonBoard[temp.y][temp.x];
            this->cannonBoard[temp.y][temp.x] = nullptr;
        }
    }

    

    // Removing the white pieces
    loop(j, 0, columns) {
        if(j % 2 == 0) {
            //Townhall *townhall = new Townhall(Position(j, 0), Colour::white);
            if (this->cannonBoard[0][j] != nullptr){
                delete this->cannonBoard[0][j];
                this->cannonBoard[0][j] = nullptr;
            }

        }
    }

    
    // Removing the black pieces
    loop(j, 0, columns) {
        int y = rows - 1;
        if(j % 2 == 1) {
            //Townhall *townhall = new Townhall(Position(j, y), Colour::black);
            if (this->cannonBoard[y][j] != nullptr){
                delete this->cannonBoard[y][j];
                this->cannonBoard[y][j] = nullptr;
            }
        }
    }

    cout<<"There"<<endl;
    
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
