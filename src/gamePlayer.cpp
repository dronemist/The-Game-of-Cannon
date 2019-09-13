#include <iostream>
#include "gamePlayer.h"

using namespace std;

// TODO: incorporate evaluation function in this
GamePlayer::GamePlayer(Colour colour, int ply, int row, int column) {
    this->currentState = new State(row, column, colour);
    this->ply = ply;
}

string GamePlayer::play() {
    string optimalMove = "";
    int val = minimax(1, this->currentState, true, this->ply, optimalMove, INT32_MIN, INT32_MAX, this->currentState->colourOfCurrentPlayer);

    // changing board of current state
    this->currentState->makeMove(optimalMove, this->currentState->currentBoard);
    // cout<<val<<endl;
    return optimalMove;
}
