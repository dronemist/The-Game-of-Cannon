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
    iterativeDeepening(this->currentState, this->ply, this->currentState->colourOfCurrentPlayer);
    // int val = minimax(0, this->currentState, true, this->ply, optimalMove, INT32_MIN, INT32_MAX, this->currentState->colourOfCurrentPlayer);
    // string ans = "";
    // (this->currentState->getStringValue(ans));
    // cout<<ans<<endl;
    // changing board of current state
    // this->currentState->makeMove(optimalMove, this->currentState->currentBoard);
    // cout<<val<<endl;
    return optimalMove;
}
