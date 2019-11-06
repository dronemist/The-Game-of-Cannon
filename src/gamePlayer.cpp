#include <iostream>
#include "gamePlayer.h"

using namespace std;

// TODO: incorporate evaluation function in this
GamePlayer::GamePlayer(Colour colour, int ply, int row, int column) {
    this->currentState = new State(row, column, colour);
    this->ply = ply;
}

string GamePlayer::play(bool learn) {
    string optimalMove = "";

    // Expected value of the current state
    double expectedValue;
    // Actual value of the current state
    double actualValue = minimax(0, this->currentState, true, this->ply, optimalMove, double(INT32_MIN), double(INT32_MAX), this->currentState->colourOfCurrentPlayer);
    // learning rate
    // ? preferably decrease as model learns
    double learningRate = 0.01;
    if (learn) {
        vector<double> features;
        expectedValue = this->currentState->getValue(this->currentState->colourOfCurrentPlayer, features);
        for(int i = 0; i < parameters.size(); i++) {
            cout<<parameters[i]<<" ";
            parameters[i] += ((actualValue - expectedValue) * learningRate * features[i]);
            cout<<parameters[i]<<" "<<endl; 
        }
        for(int i = 0; i < parameters.size(); i++) {
            cout<<features[i]<<" ";
        }
    }
    // changing board of current state
    this->currentState->makeMove(optimalMove, this->currentState->currentBoard);
    // cout<<val<<endl;
    return optimalMove;
}
