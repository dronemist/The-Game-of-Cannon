#include <iostream>
#include <sstream>
#include <algorithm>
#include "state.h"

#define loop(i, start, end) for(int i = start; i < end; i++)

using namespace std;

void State::removePositonFromBoard(Board &newBoard, int x, int y) {
    if(newBoard.cannonBoard[y][x] != nullptr) {
        int pos =
        newBoard.cannonBoard[y][x]->getColour() == Colour::black ? 0 : 1;
        vector<Position>::iterator findIter =
        find(newBoard.positionsOfSoldiersOnBoard[pos].begin(), newBoard.positionsOfSoldiersOnBoard[pos].end(),
        Position(x, y));
        if(findIter != newBoard.positionsOfSoldiersOnBoard[pos].end())
        {
            newBoard.positionsOfSoldiersOnBoard[pos].erase(findIter);
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

void State::expand(vector<State*> &answer) {
    // DOUBT: is it okay to make a copy?
    // vector<State*> answer;
    vector<Position> currentList =
    this->colourOfCurrentPlayer == Colour::black ?
    this->currentBoard.positionsOfSoldiersOnBoard[0] : this->currentBoard.positionsOfSoldiersOnBoard[1];

    vector<Position> :: iterator it;
    for(it = currentList.begin(); it != currentList.end(); ++it) {

        // If the piece is the same colour as the current piece
        // TODO: change if differenet lists exist
        // if(this->currentBoard.cannonBoard[it->y][it->x]->getColour() == this->colourOfCurrentPlayer) {
        vector<string> moves;
        this->currentBoard.cannonBoard[it->y][it->x]->getAllowedMoves(this->currentBoard, (& (*it)), moves);
        loop(i, 0, moves.size()) {
            State *newState = new State();
            // DOUBT: this assignment makes copies
            newState->currentBoard = this->currentBoard;
            // make move on the new state
            this->makeMove(moves[i], newState->currentBoard);
            // Assigning rest of the variables
            newState->moveFromPreviousState = moves[i];
            newState->colourOfCurrentPlayer =
            this->colourOfCurrentPlayer == Colour::black ? Colour::white : Colour::black;
            newState->previousState = this;
            answer.push_back(newState);
        }
    }
    // return answer;
}

void State::makeMove(string move, Board &newBoard) {

    istringstream ss(move);
    string token, typeOfMove;
    int count = 0;
    int xInitial, xFinal, yInitial, yFinal;

    if(move == ""){
        cout<<"No moves remaining, exiting"<<endl;
        exit(0);
    }

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

        // adding final to this->colour piece list
        if(newBoard.cannonBoard[yInitial][xInitial]->getColour() == Colour::black)
            newBoard.positionsOfSoldiersOnBoard[0].push_back(Position(xFinal, yFinal));
        else
            newBoard.positionsOfSoldiersOnBoard[1].push_back(Position(xFinal, yFinal));
        // removing final from opposite of this->colour piece list
        this->removePositonFromBoard(newBoard, xFinal, yFinal);
        newBoard.cannonBoard[yFinal][xFinal] = newBoard.cannonBoard[yInitial][xInitial];
        // removing initial from this->colour piece list
        this->removePositonFromBoard(newBoard, xInitial, yInitial);
        newBoard.cannonBoard[yInitial][xInitial] = nullptr;
    } else {
        this->removePositonFromBoard(newBoard, xFinal, yFinal);
        newBoard.cannonBoard[yFinal][xFinal] = nullptr;
    }

}

int State::getValue(Colour colour) {
    int blackSoldiers = this->currentBoard.positionsOfSoldiersOnBoard[0].size();
    int whiteSoldiers = this->currentBoard.positionsOfSoldiersOnBoard[1].size();
    int blackTownhalls = this->currentBoard.numberOfBlackTownhalls();
    int whiteTownhalls = this->currentBoard.numberOfWhiteTownhalls();
    int blackCannons = this->currentBoard.numberOfCannonsOnBoard(this->currentBoard.positionsOfSoldiersOnBoard, 0);
    int whiteCannons = this->currentBoard.numberOfCannonsOnBoard(this->currentBoard.positionsOfSoldiersOnBoard, 1);

    int value = (blackSoldiers - whiteSoldiers) + 50 * (blackTownhalls - whiteTownhalls) + 10 * (blackCannons - whiteCannons);

    if(colour == Colour::black)
        return value;
    else
    {
        return -value;
    }
}
// TODO: should this be a pointer
bool comparePosition(Position p1, Position p2) {
    if(p2.y > p1.y)
        return true;
    else if(p2.y == p1.y) {
        if(p2.x >= p1.x)
            return true;
        return false;    
    } 
    else {
        return false;
    }    
}
string State::getStringValue(/*string &answer*/) {
    string answer = "";
    // adding black soldiers
    vector<Position> allPiecePosition = this->currentBoard.positionsOfSoldiersOnBoard[0];
    // adding white soldiers
    allPiecePosition.insert(allPiecePosition.end(), this->currentBoard.positionsOfSoldiersOnBoard[1].begin(), this->currentBoard.positionsOfSoldiersOnBoard[1].end());
    // adding white townhalls
    for(int j = 0; j < this->currentBoard.getColumns(); j += 2) {
        if(this->currentBoard.cannonBoard[0][j] != nullptr &&
        this->currentBoard.cannonBoard[0][j]->getType() == PieceType::townhall){
            allPiecePosition.push_back(Position(j, 0));
        }
    }
    int rows = this->currentBoard.getRows();
    // adding black townhalls
    for(int j = 1; j < this->currentBoard.getColumns(); j += 2) {
        if(this->currentBoard.cannonBoard[rows - 1][j] != nullptr &&
        this->currentBoard.cannonBoard[rows - 1][j]->getType() == PieceType::townhall){
            allPiecePosition.push_back(Position(j, rows - 1));
        }
    }
    sort(allPiecePosition.begin(), allPiecePosition.end(), comparePosition);
    loop(i, 0, allPiecePosition.size()) {
        answer += intToString(allPiecePosition[i].x);
        answer += intToString(allPiecePosition[i].y);
    }
    return answer;
}  