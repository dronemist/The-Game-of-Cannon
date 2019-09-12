#include <iostream>
#include "gamePlayer.h"

using namespace std;

int main() {
    string move = "";
    GamePlayer g1(Colour::black, 5);
    GamePlayer g2(Colour::white, 5);
    while (true)
    {   
        move = g1.play();
        cout<<"g1 played "<<move<<endl;
        g1.currentState->currentBoard.printBoard();
        g2.currentState->makeMove(move, g2.currentState->currentBoard);
        move = g2.play();
        g1.currentState->makeMove(move, g1.currentState->currentBoard);
        cout<<"g2 played "<<move<<endl;
        g2.currentState->currentBoard.printBoard();
    }
}
