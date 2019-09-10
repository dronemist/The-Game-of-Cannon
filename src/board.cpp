#include <iostream>
#include "board.h"
#define loop(i, start, end) for(int i = start; i < end; i++)
using namespace std;


Board::Board(int rows, int columns) {
    this->columns = columns;
    this->rows = rows;
    // Initialising as null 
    this->cannonBoard = vector<vector<Piece*>> (rows, vector<Piece*>(columns));
    // filling the white pieces
    loop(j, 0, columns) {
        if(j % 2 == 0) {
            Townhall *townhall = new Townhall(Position(j, 0), Colour::white);
            this->cannonBoard[0][j] = townhall;
            
        } else {
            Soldier *soldier = new Soldier(Position(j, 0), Colour::white);
            this->cannonBoard[0][j] = soldier;
            Soldier *soldier2 = new Soldier(Position(j, 1), Colour::white);
            this->cannonBoard[1][j] = soldier2;
            Soldier *soldier3 = new Soldier(Position(j, 2), Colour::white);
            this->cannonBoard[2][j] = soldier3;
        }
    }
    // filling the black pieces
    loop(j, 0, columns) {
        int y = rows - 1;
        if(j % 2 == 1) {
            Townhall *townhall = new Townhall(Position(j, y), Colour::black);
            this->cannonBoard[y][j] = townhall;
        } else {
            Soldier *soldier = new Soldier(Position(j, y), Colour::black);
            this->cannonBoard[y][j] = soldier;
            Soldier *soldier2 = new Soldier(Position(j, y - 1), Colour::black);
            this->cannonBoard[y - 1][j] = soldier2;
            Soldier *soldier3 = new Soldier(Position(j, y - 2), Colour::black);
            this->cannonBoard[y - 2][j] = soldier3;
        }
    }
}

void Board::printBoard() {
    loop(i, 0, this->rows) {
        loop(j, 0, this->columns) {
            if(this->cannonBoard[i][j] == nullptr) {
                cout<<" ";
            } else { 
                if(this->cannonBoard[i][j]->getType() == PieceType::soldier) 
                    cout<<"S";
                else if(this->cannonBoard[i][j]->getType() == PieceType::townhall)
                    cout<<"T";
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

int main() {
    Board x;
    x.printBoard();
}