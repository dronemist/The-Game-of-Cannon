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


bool isAllySoldierPresent(Piece* ptr, int soldierColor){
  if(ptr != nullptr && int(ptr->getColour()) == soldierColor && ptr->getType() == PieceType::soldier)
    return true;
  return false;
}


// int State::scoreOfSoldiersOnBoard(){
//
//
// }
//
// int State::scoreOfCannonsOnBoard(int colourOfPlayerToBeEvaluated){  // Piece color 0 for black, 1 for white
//
//   Board* board = this->currentBoard;
//   vector< vector<Position> >* positionsOfSoldiersOnBoard = &(board->positionsOfSoldiersOnBoard);
//
//   int numRows = board->getRows();
//   int numCols = board->getColumns();
//   int count = 0;
//
//
//
//   for(vector<Position>::iterator it = positionsOfSoldiersOnBoard[colourOfPlayerToBeEvaluated].begin(); it != positionsOfSoldiersOnBoard[colourOfPlayerToBeEvaluated].end(); ++it){
//
//     int x = it-> x;
//     int y = it-> y;
//
//     bool isLeftMostOfHorizontalCannon = ((x + 2) < numCols) && isAllySoldierPresent(board->cannonBoard[y][x+1], colourOfPlayerToBeEvaluated)
//                                         && isAllySoldierPresent(board->cannonBoard[y][x+2], colourOfPlayerToBeEvaluated);
//
//     bool isTopLeftMostOfCannon = ((x+2) < numCols) && ((y+2) < numRows) && isAllySoldierPresent(board->cannonBoard[y+1][x+1], colourOfPlayerToBeEvaluated)
//                                   && isAllySoldierPresent(board->cannonBoard[y+2][x+2], colourOfPlayerToBeEvaluated);
//
//     bool isTopMostOfVerticalCannon = ((y+2) < numRows) && isAllySoldierPresent(board->cannonBoard[y+1][x], colourOfPlayerToBeEvaluated)
//                                      && isAllySoldierPresent(board->cannonBoard[y+2][x], colourOfPlayerToBeEvaluated);
//
//     bool isTopRightMostOfCannon = ((x-2) >= 0) && ((y+2) < numRows) && isAllySoldierPresent(board->cannonBoard[y+1][x-1], colourOfPlayerToBeEvaluated)
//                                   && isAllySoldierPresent(board->cannonBoard[y + 2][x - 2], colourOfPlayerToBeEvaluated);
//
//     if(isLeftMostOfHorizontalCannon){
//
//     }
//
//     count += isLeftMostOfHorizontalCannon + isTopLeftMostOfCannon + isTopMostOfVerticalCannon + isTopRightMostOfCannon;
//
//   }
//
//   return count;
//
// }

void State::calculateStateScoreParameters(int colourOfPlayerToBeEvaluated, int* defenceScoreRightWing, int* offenceScoreRightWing,
                                        int* defenceScoreLeftWing, int* offenceScoreLeftWing,
                                        int* defenceScoreCenter, int* offenceScoreCenter, vector<int> &parameters)  //parameters[0] for coefficient of horizontal cannon, 1 for diagonal, 2 for vertical
  {
    Board* board = &(this->currentBoard);
    vector< vector<Position> >* positionsOfSoldiersOnBoard = &(board->positionsOfSoldiersOnBoard);

    int numRows = board->getRows();
    int numCols = board->getColumns();
    int count = 0;

    //Calculating the score because of soldiers
    for(vector<Position>::iterator it = (*positionsOfSoldiersOnBoard)[colourOfPlayerToBeEvaluated].begin(); it != (*positionsOfSoldiersOnBoard)[colourOfPlayerToBeEvaluated].end(); ++it){

      int x = it-> x;
      int y = it-> y;

      *defenceScoreLeftWing = (*defenceScoreLeftWing) + 2 * (colourOfPlayerToBeEvaluated == int(Colour::black)? (y) : (numRows - y - 1)) * (x < numCols/2);
      *offenceScoreLeftWing = (*offenceScoreLeftWing) + 2 * (colourOfPlayerToBeEvaluated == int(Colour::black)?  (numRows - y - 1) : (y)) * (x < numCols/2);
      *defenceScoreRightWing = (*defenceScoreRightWing) + 2 * (colourOfPlayerToBeEvaluated == int(Colour::black)? (y) : (numRows - y - 1)) * (x >= numCols/2);
      *offenceScoreRightWing = (*offenceScoreRightWing) + 2 * (colourOfPlayerToBeEvaluated == int(Colour::black)?  (numRows - y - 1) : (y)) * (x >= numCols/2);
  }



    //Calculating the score because of cannons
    for(vector<Position>::iterator it = (*positionsOfSoldiersOnBoard)[colourOfPlayerToBeEvaluated].begin(); it != (*positionsOfSoldiersOnBoard)[colourOfPlayerToBeEvaluated].end(); ++it){

      int x = it-> x;
      int y = it-> y;

      bool isLeftMostOfHorizontalCannon = ((x + 2) < numCols) && isAllySoldierPresent(board->cannonBoard[y][x+1], colourOfPlayerToBeEvaluated)
                                          && isAllySoldierPresent(board->cannonBoard[y][x+2], colourOfPlayerToBeEvaluated);

      bool isTopLeftMostOfCannon = ((x+2) < numCols) && ((y+2) < numRows) && isAllySoldierPresent(board->cannonBoard[y+1][x+1], colourOfPlayerToBeEvaluated)
                                    && isAllySoldierPresent(board->cannonBoard[y+2][x+2], colourOfPlayerToBeEvaluated);

      bool isTopMostOfVerticalCannon = ((y+2) < numRows) && isAllySoldierPresent(board->cannonBoard[y+1][x], colourOfPlayerToBeEvaluated)
                                       && isAllySoldierPresent(board->cannonBoard[y+2][x], colourOfPlayerToBeEvaluated);

      bool isTopRightMostOfCannon = ((x-2) >= 0) && ((y+2) < numRows) && isAllySoldierPresent(board->cannonBoard[y+1][x-1], colourOfPlayerToBeEvaluated)
                                    && isAllySoldierPresent(board->cannonBoard[y + 2][x - 2], colourOfPlayerToBeEvaluated);

                                    //Currently doing defence offence only
      if(isLeftMostOfHorizontalCannon){
        *defenceScoreLeftWing = (*defenceScoreLeftWing) + parameters[0] * (colourOfPlayerToBeEvaluated == int(Colour::black)? (y) : (numRows - y -1)) * (x + 1 >= numCols/2 + 1);
        *defenceScoreRightWing = (*defenceScoreLeftWing) + parameters[0] * (colourOfPlayerToBeEvaluated == int(Colour::black)? (y) : (numRows - y -1)) * (x + 1 < numCols/2 + 1);
      }

      if(isTopMostOfVerticalCannon){
        *offenceScoreLeftWing = (*offenceScoreLeftWing) + parameters[2] * (colourOfPlayerToBeEvaluated == int(Colour::black)? (numRows - (y+1)) * (2 - x%2 ) : (y + 1) * (1 + x%2)) * (x < numCols/2);
        *offenceScoreRightWing = (*offenceScoreRightWing) + parameters[2] * (colourOfPlayerToBeEvaluated == int(Colour::black)? (numRows - (y+1)) * (2 - x%2) : (y + 1) * (1 + x%2)) * (x >= numCols/2);
      }

      if(isTopRightMostOfCannon){
        *defenceScoreLeftWing = (*defenceScoreLeftWing) + parameters[1];
        *offenceScoreLeftWing = (*offenceScoreLeftWing) + parameters[1];
        *defenceScoreRightWing = (*defenceScoreRightWing) + parameters[1];
        *offenceScoreRightWing = (*offenceScoreRightWing) + parameters[1];
      }

      if(isTopLeftMostOfCannon){
        *defenceScoreLeftWing = (*defenceScoreLeftWing) + parameters[1];
        *offenceScoreLeftWing = (*offenceScoreLeftWing) + parameters[1];
        *defenceScoreRightWing = (*defenceScoreRightWing) + parameters[1];
        *offenceScoreRightWing = (*offenceScoreRightWing) + parameters[1];
      }
      // if()
      // count += isLeftMostOfHorizontalCannon + isTopLeftMostOfCannon + isTopMostOfVerticalCannon + isTopRightMostOfCannon;

    }

  }

int State::getValue(Colour colourOfPlayerToBeEvaluated, Colour colourOfMovingPlayer) {

    bool isOurMove = colourOfPlayerToBeEvaluated == colourOfMovingPlayer; //True if we have to move and false if opponent has to move

    int blackSoldiers = this->currentBoard.positionsOfSoldiersOnBoard[0].size();
    int whiteSoldiers = this->currentBoard.positionsOfSoldiersOnBoard[1].size();
    int blackTownhalls = this->currentBoard.numberOfBlackTownhalls();
    int whiteTownhalls = this->currentBoard.numberOfWhiteTownhalls();


    int defenceScoreRightWingBlack = 0; //NOTE: Right left with respect to our screen, not with respect to rotation of board
    int offenceScoreRightWingBlack = 0;
    int defenceScoreLeftWingBlack = 0;
    int offenceScoreLeftWingBlack = 0;
    int defenceScoreCenterBlack = 0;
    int offenceScoreCenterBlack = 0;
    int differenceOfSoldier;
    vector<int> parameters = {1, 1, 1};
    this->calculateStateScoreParameters(0, &defenceScoreRightWingBlack, &offenceScoreRightWingBlack,
                                                                            &defenceScoreLeftWingBlack, &offenceScoreLeftWingBlack,
                                                                            &defenceScoreCenterBlack, &offenceScoreCenterBlack, parameters);

    int defenceScoreRightWingWhite = 0; //NOTE: Right left with respect to our screen, not with respect to rotation of board
    int offenceScoreRightWingWhite = 0;
    int defenceScoreLeftWingWhite = 0;
    int offenceScoreLeftWingWhite = 0;
    int defenceScoreCenterWhite = 0;
    int offenceScoreCenterWhite = 0;

    this->calculateStateScoreParameters(1, &defenceScoreRightWingWhite, &offenceScoreRightWingWhite,
                                                                            &defenceScoreLeftWingWhite, &offenceScoreLeftWingWhite,
                                                                            &defenceScoreCenterWhite, &offenceScoreCenterWhite, parameters);

    int value;
    // int blackOffenceScore = (blackSoldiers - whiteSoldiers) + 100 * (blackTownhalls - whiteTownhalls) + 10 * (defenceScoreLeftWingBlack - offenceScoreLeftWingWhite);
    int temp = max(offenceScoreLeftWingBlack + defenceScoreLeftWingBlack - defenceScoreLeftWingWhite - offenceScoreLeftWingWhite, defenceScoreRightWingBlack + offenceScoreRightWingBlack - offenceScoreRightWingWhite - defenceScoreRightWingWhite);
    temp = max(temp, offenceScoreLeftWingBlack + defenceScoreLeftWingBlack - defenceScoreLeftWingWhite - offenceScoreLeftWingWhite + defenceScoreRightWingBlack + offenceScoreRightWingBlack - offenceScoreRightWingWhite - defenceScoreRightWingWhite);

    if(blackTownhalls > whiteTownhalls || (blackTownhalls == whiteTownhalls && colourOfPlayerToBeEvaluated == Colour::black)){

      value = 10000 * (blackTownhalls - whiteTownhalls) + 0 * (defenceScoreLeftWingBlack - offenceScoreLeftWingWhite) + 1 * temp;
    }
    else {
      value = 10000 * (blackTownhalls - whiteTownhalls) + 1 * (temp) + 0 * (offenceScoreLeftWingBlack - defenceScoreLeftWingWhite);
    }
    // TODO: check this if loop
    if(whiteTownhalls == 2 && colourOfPlayerToBeEvaluated == Colour::black) {
        value = 1000000;
    } else if(blackTownhalls == 2 && colourOfPlayerToBeEvaluated == Colour::white) {
        value = 1000000;
    }
    if(colourOfPlayerToBeEvaluated == Colour::black)
        return value;
    else
    {
        return -value;
    }
}
