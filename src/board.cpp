#include <iostream>
#include "board.h"
#define loop(i, start, end) for(int i = start; i < end; i++)
using namespace std;


Board::Board(int rows, int columns) {
    this->columns = columns;
    this->rows = rows;
    // Initialising as null
    this->cannonBoard = vector<vector<Piece*>> (rows, vector<Piece*>(columns, nullptr));
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

            //Inserting these soldier positions into list of soldiers positions
            positionsOfSoldiersOnBoard.push_back(Position(j, 0));
            positionsOfSoldiersOnBoard.push_back(Position(j, 1));
            positionsOfSoldiersOnBoard.push_back(Position(j, 2));
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

            //Inserting these soldier positions into list of soldier positions
            positionsOfSoldiersOnBoard.push_back(Position(j, y));
            positionsOfSoldiersOnBoard.push_back(Position(j, y - 1));
            positionsOfSoldiersOnBoard.push_back(Position(j, y - 2));
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
    Position* pos = new Position(0, 5);
    vector<string> temp = x.cannonBoard[5][0]->getAllowedMoves(x, pos);
    loop(i, 0, temp.size()) {
        cout<<temp[i]<<endl;
    }
}
