#include <iostream>
#include <fstream>
#include <cmath>
#include "gamePlayer.h"

using namespace std;

// TODO: incorporate evaluation function in this
GamePlayer::GamePlayer(Colour colour, int ply, int row, int column) {
    // cout<<"Hi"<<endl;
    this->currentState = new State(row, column, colour);
    this->ply = ply;
    /*// Initialising parameters
    ifstream weightsFile;
    // For the player which is undergoing training
    // weightsFile.open("current_weights.txt");
    // For the best player till now
    weightsFile.open("best_weights.txt");


    int count = 0;
    string weight_string;

    while(weightsFile >> weight_string){
         parameters[count] = stod(weight_string);
         ++count;
     }

     weightsFile.close();*/
}

string GamePlayer::play(bool learn) {


    string optimalMove = "";

    // Expected value of the current state
    double expectedValue;
    // Actual value of the current state
    double actualValue = minimax(0, this->currentState, true, this->ply, optimalMove, -(__DBL_MAX__ - 1), __DBL_MAX__, this->currentState->colourOfCurrentPlayer);
    // learning rate
    //  cout<<"Hi"<<endl;
    // ? preferably decrease as model learns
    double learningRate = 0.0001;

    if (learn) {
        // writing weights to file
        ofstream outputLog;
        outputLog.open("current_weights.txt");

        vector<double> features;
        expectedValue = this->currentState->getValue(this->currentState->colourOfCurrentPlayer, features);
        for(int i = 0; i < parameters.size(); i++) {
            double diff = actualValue - expectedValue;
            if(abs(diff) < 5000)
                parameters[i] += ((actualValue - expectedValue) * learningRate * features[i]);
        }
        for(int i = 0; i < parameters.size(); i++) {
            outputLog<<parameters[i]<<" ";
        }
        outputLog<<endl;
        outputLog.close();
    }
    // changing board of current state
    this->currentState->makeMove(optimalMove, this->currentState->currentBoard);
    // cout<<val<<endl;
    return optimalMove;
}
