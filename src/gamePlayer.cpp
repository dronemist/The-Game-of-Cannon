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
    double val = minimax(0, this->currentState, true, this->ply, optimalMove, double(INT32_MIN), double(INT32_MAX), this->currentState->colourOfCurrentPlayer);

    // changing board of current state
    this->currentState->makeMove(optimalMove, this->currentState->currentBoard);
    // cout<<val<<endl;
    return optimalMove;
}
