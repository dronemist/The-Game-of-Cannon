#include <iostream>
#include "gamePlayer.h"

using namespace std;

int main() {
    string move = "";
    int id, rows, column, time;
    cin>>id>>rows>>column>>time;
    Colour colour = id == 0 ? Colour::black : Colour::white;
    GamePlayer g1(colour, 5);
    if(id == 0) {
        move = g1.play();
        cout<<move<<endl;
    }
    // GamePlayer g2(Colour::white, 5);

    // int rows = g1.currentState->currentBoard.getRows();
    // int columns = g1.currentState->currentBoard.getColumns();



    // Board temp_board = Board();

    // for(int i = 0; i<rows; ++i){
    //   for(int j=0; j<columns; ++j){
    //     temp_board.cannonBoard[i][j] = nullptr;
    //   }
    // }

    // temp_board.positionsOfSoldiersOnBoard[0].clear();
    // temp_board.positionsOfSoldiersOnBoard[1].clear();

    // temp_board.cannonBoard[0][0] = new Soldier(Colour::black);
    // temp_board.cannonBoard[1][1] = new Soldier(Colour::black);

    // temp_board.positionsOfSoldiersOnBoard[0].push_back(Position(0,0));
    // temp_board.positionsOfSoldiersOnBoard[0].push_back(Position(1,1));


    // temp_board.cannonBoard[7][3] = new Soldier(Colour::white);
    // temp_board.cannonBoard[7][4] = new Soldier(Colour::white);
    // temp_board.cannonBoard[7][5] = new Soldier(Colour::white);
    // temp_board.cannonBoard[7][6] = new Soldier(Colour::white);
    // temp_board.cannonBoard[7][7] = new Soldier(Colour::white);

    // temp_board.positionsOfSoldiersOnBoard[1].push_back(Position(3,7));
    // temp_board.positionsOfSoldiersOnBoard[1].push_back(Position(4,7));
    // temp_board.positionsOfSoldiersOnBoard[1].push_back(Position(5,7));
    // temp_board.positionsOfSoldiersOnBoard[1].push_back(Position(6,7));
    // temp_board.positionsOfSoldiersOnBoard[0].push_back(Position(7,7));

    // temp_board.cannonBoard[0][4] = new Townhall(Position(4, 0), Colour::white);
    // temp_board.cannonBoard[0][6] = new Townhall(Position(6, 0), Colour::white);
    // temp_board.cannonBoard[0][2] = new Townhall(Position(2, 0), Colour::white);

    // temp_board.cannonBoard[7][1] = new Townhall(Position(1, 7), Colour::black);

    // g1.currentState->currentBoard = temp_board;
    // g2.currentState->currentBoard = temp_board;

    // int numMoves = 5;
    // cout<<"hi"<<endl;
    while(true) {
        cin.ignore();
        getline(cin, move);
        // cout<<"g1 played "<<move<<endl;
        // g1.currentState->currentBoard.printBoard();
        // g2.currentState->makeMove(move, g2.currentState->currentBoard);
        // move = g2.play();
        g1.currentState->makeMove(move, g1.currentState->currentBoard);
        move = g1.play();
        
        cout<<move<<endl;
        // cout<<"g2 played "<<move<<endl;
        // g2.currentState->currentBoard.printBoard();
    }

}
