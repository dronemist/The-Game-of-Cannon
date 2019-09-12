#include <iostream>
#include "gamePlayer.h"

using namespace std;

// TODO: incorporate evaluation function in this
GamePlayer::GamePlayer(Colour colour, int ply) {
    this->currentState = new State(8, 8, colour);
    this->ply = ply;
}

string GamePlayer::play() {
    string optimalMove = "";
    minimax(1, this->currentState, true, this->ply, optimalMove, INT32_MIN, INT32_MAX);
    cout<<optimalMove<<endl;
    // changing board of current state
    this->currentState->makeMove(optimalMove, this->currentState->currentBoard);
    return optimalMove;
}
