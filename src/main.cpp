#include <iostream>
#include <sstream>
#include <ctime> 
#include "gamePlayer.h"

using namespace std;

int main() {
    string move = "";
    string input = "";
    // Taking input
    getline(cin, input);
    int id, rows, column, time;
    istringstream ss(input);
    string token;
    int count = 0;
    while(ss>>token) {
        switch (count)
        {
        case 0:
            id = stoi(token);
            count++;
            break;
        case 1:
            rows = stoi(token);
            count++;
            break;
        case 2:
            column = stoi(token);
            count++;
            break;
        case 3:
            time = stoi(token);
            count++;
            break;
        default:
            break;
        }
    }
    clock_t begin = clock();
    Colour colour = id == 1 ? Colour::black : Colour::white;
    GamePlayer g1(colour, 4, rows, column);
    if(id == 1) {
        move = g1.play();
        cout<<move<<endl;
    }
    // g1.currentState->currentBoard.printBoard();
    clock_t end;
    double elapsedSeconds;
    double timeRemaining;
    int numberOfPlayers = 24;
    clock_t timeTemp1;
    clock_t timeTemp2;
    float timeForOtherUser = 0;
    while(true) {
        timeTemp1 = clock();
        getline(cin, move);
        timeTemp2 = clock();
        timeForOtherUser += (timeTemp2 - timeTemp1)/(CLOCKS_PER_SEC);
        // cout<<move<<endl;
        // cout<<"g1 played "<<move<<endl;
        // g1.currentState->currentBoard.printBoard();
        // g2.currentState->makeMove(move, g2.currentState->currentBoard);
        // move = g2.play();
        g1.currentState->makeMove(move, g1.currentState->currentBoard);
        move = g1.play();

        cout<<move<<endl;
        // cout<<"g2 played "<<move<<endl;
        // g2.currentState->currentBoard.printBoard();
        end = clock();
        elapsedSeconds = (end - begin - timeForOtherUser)/(CLOCKS_PER_SEC);
        timeRemaining = time - elapsedSeconds;
        numberOfPlayers = g1.currentState->currentBoard.positionsOfSoldiersOnBoard[0].size() 
                            + g1.currentState->currentBoard.positionsOfSoldiersOnBoard[1].size();
        
        if(numberOfPlayers <= 12 && timeRemaining > 20){
            g1.ply = 5;
        }
        else {
            g1.ply = 4;
        }
    }

}
