#include <iostream>
#include <sstream>
#include <algorithm>
#include "state.h"
#define loop(i, start, end) for(int i = start; i < end; i++)

using namespace std;

State::State(int rows, int columns, Colour colour) {
    Board b(rows, columns);
    this->currentBoard = b;
    this->moveFromPreviousState = "";
    this->previousState = nullptr;
    // adding a default value
    this->colourOfCurrentPlayer = colour;
}

vector<State*> State::expand() {
    // DOUBT: is it okay to make a copy?
    vector<State*> answer;
    list<Position> currentList =
    this->colourOfCurrentPlayer == Colour::black ? this->currentBoard.positionsOfSoldiersOnBoard[0] : this->currentBoard.positionsOfSoldiersOnBoard[1];

    list<Position> :: iterator it;
    for(it = currentList.begin(); it != currentList.end(); ++it) {

        // If the piece is the same colour as the current piece
        // TODO: change if differenet lists exist
        // if(this->currentBoard.cannonBoard[it->y][it->x]->getColour() == this->colourOfCurrentPlayer) {
          vector<string> moves = this->currentBoard.cannonBoard[it->y][it->x]->getAllowedMoves(this->currentBoard, (& (*it)));
          loop(i, 0, moves.size()) {
              State *newState = new State();
              // DOUBT: this assignment makes copies
              newState->currentBoard = this->currentBoard;
              // make move on the new state
              this->makeMove(moves[i], newState->currentBoard);
              newState->moveFromPreviousState = moves[i];
              newState->colourOfCurrentPlayer =
              this->colourOfCurrentPlayer == Colour::black ? Colour::white : Colour::black;
              newState->previousState = this;
              answer.push_back(newState);
          }
        // }
    }
    cout<<this->moveFromPreviousState<<endl;
    return answer;
}

void State::makeMove(string move, Board &newBoard) {

    istringstream ss(move);
    string token, typeOfMove;
    int count = 0;
    int xInitial, xFinal, yInitial, yFinal;
    while(ss>>token) {
        switch (count)
        {
        case 0:
            if(token == "S")
                count++;
            else
                throw exception();
            break;
        case 1:
            xInitial = stoi(token);
            count++;
        case 2:
            yInitial = stoi(token);
            count++;
        case 3:
            typeOfMove = token;
        case 4:
            xFinal = stoi(token);
            count++;
        case 5:
            yFinal = stoi(token);
            count++;
        default:
            break;
        }
    }
    // Removing position from list
    if(newBoard.cannonBoard[yFinal][xFinal] != nullptr) {
        int colourOfOpposition =
        this->colourOfCurrentPlayer == Colour::black ? 1 : 0; //If current player is black, opposition is white
        list<Position>::iterator findIter =
        find(newBoard.positionsOfSoldiersOnBoard[colourOfOpposition].begin(), newBoard.positionsOfSoldiersOnBoard[colourOfOpposition].end(),
        Position(xFinal, yFinal));
        if(findIter != newBoard.positionsOfSoldiersOnBoard[colourOfOpposition].end())
        {
            newBoard.positionsOfSoldiersOnBoard[colourOfOpposition].erase(findIter);
        }
    }
    // making the move;
    if(typeOfMove == "M") {
        newBoard.cannonBoard[yFinal][xFinal] = newBoard.cannonBoard[yInitial][xInitial];
        newBoard.cannonBoard[yInitial][xInitial] = nullptr;
    } else {
        newBoard.cannonBoard[yFinal][xFinal] = nullptr;
    }

}
