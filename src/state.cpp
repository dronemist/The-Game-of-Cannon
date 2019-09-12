#include <iostream>
#include <sstream>
#include <algorithm>
#include "state.h"
#define loop(i, start, end) for(int i = start; i < end; i++)

using namespace std;

void State::removePositonFromBoard(Board &newBoard, int x, int y) {
    if(newBoard.cannonBoard[y][x] != nullptr) {
        int colourOfOppositePlayer =
        this->colourOfCurrentPlayer == Colour::black ? 1 : 0;
        list<Position>::iterator findIter =
        find(newBoard.positionsOfSoldiersOnBoard.begin(), newBoard.positionsOfSoldiersOnBoard.end(),
        Position(x, y));
        if(findIter != newBoard.positionsOfSoldiersOnBoard.end())
        {
            newBoard.positionsOfSoldiersOnBoard.erase(findIter);
        }
    }
}

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
    list<Position> currentList = this->currentBoard.positionsOfSoldiersOnBoard;
    list<Position> :: iterator it;
    for(it = currentList.begin(); it != currentList.end(); ++it) {

        // If the piece is the same colour as the current piece
        // TODO: change if differenet lists exist
        if(this->currentBoard.cannonBoard[it->y][it->x]->getColour() == this->colourOfCurrentPlayer) {
            vector<string> moves = this->currentBoard.cannonBoard[it->y][it->x]->getAllowedMoves(this->currentBoard, & (*it));
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
        }
    }
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
            if(token == "S") {
                count++;
            }
            else
                throw exception();
            break;
        case 1:
            xInitial = stoi(token);
            count++;
            break;
        case 2:
            yInitial = stoi(token);
            count++;
            break;
        case 3:
            typeOfMove = token;
            count++;
            break;
        case 4:
            xFinal = stoi(token);
            count++;
            break;
        case 5:
            yFinal = stoi(token);
            count++;
            break;
        default:
            break;
        }
    }
    
    // making the move;
    if(typeOfMove == "M") {
        if(newBoard.cannonBoard[yFinal][xFinal] == nullptr) {
            newBoard.positionsOfSoldiersOnBoard.push_back(Position(xFinal, yFinal));
        }
        newBoard.cannonBoard[yFinal][xFinal] = newBoard.cannonBoard[yInitial][xInitial];
        this->removePositonFromBoard(newBoard, xInitial, yInitial);
        newBoard.cannonBoard[yInitial][xInitial] = nullptr;
    } else {
        this->removePositonFromBoard(newBoard, xFinal, yFinal);
        newBoard.cannonBoard[yFinal][xFinal] = nullptr;
    }

}
