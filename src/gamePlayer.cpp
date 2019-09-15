#include <iostream>
#include "gamePlayer.h"

using namespace std;

// TODO: incorporate evaluation function in this
GamePlayer::GamePlayer(Colour colour, int ply, int row, int column) {
    this->temp = 2;
    this->currentState = new State(row, column, colour);
    this->colourOfPlayer = colour;
    this->ply = ply;
}

string GamePlayer::play() {
    string optimalMove = "";
    if(this->colourOfPlayer == Colour::white && this->temp != 0) {
        if(this->temp == 2)
            optimalMove = "S 5 0 M 6 1";
        else    
            optimalMove = "S 3 0 M 2 1";
        this->temp--;
    }
    // } else if(this->colourOfPlayer == Colour::black && this->temp != 0) {
    //     if(this->temp == 2)
    //         optimalMove = "S 2 7 M 1 6";
    //     else    
    //         optimalMove = "S 4 7 M 5 6";
    //     this->temp--;
    // } 
    else {
        int val = minimax(0, this->currentState, true, this->ply, optimalMove, INT32_MIN, INT32_MAX, this->currentState->colourOfCurrentPlayer);
    }
    // changing board of current state
    this->currentState->makeMove(optimalMove, this->currentState->currentBoard);
    // cout<<val<<endl;
    return optimalMove;
}
