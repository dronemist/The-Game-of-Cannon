#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include "state.h"
#define loop(i, start, end) for(int i = start; i < end; i++)

using namespace std;

// Parameters for getValue
/*
* 0 : horizontal cannon
* 1 : diagonal cannon
* 2 : vertical cannon
* 3 : townhall
* 4 : soldier attack
* 5 : soldier defence
*/
vector<double> parameters = {1.0, 1.0, 1.0, 10000.0, 3.0, 2.0};


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
    // Determining which soldier list to expand
    vector<Position> currentList =
    this->colourOfCurrentPlayer == Colour::black ?
    this->currentBoard.positionsOfSoldiersOnBoard[0] : this->currentBoard.positionsOfSoldiersOnBoard[1];

    vector<Position> :: iterator it;
    for(it = currentList.begin(); it != currentList.end(); ++it) {

        // If the piece is the same colour as the current piece
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
void State::calculateStateScoreParameters(int colourOfPlayerToBeEvaluated, double* defenceScoreRightWing, double* offenceScoreRightWing,
                                        double* defenceScoreLeftWing, double* offenceScoreLeftWing) {
  // Current board and soldiers
  Board* board = &(this->currentBoard);
  vector< vector<Position> >* positionsOfSoldiersOnBoard = &(board->positionsOfSoldiersOnBoard);

  int numRows = board->getRows();
  int numCols = board->getColumns();
  int count = 0;

  // Calculating the score because of soldiers
  double soldierAttack = parameters[4];
  double soldierDefend = parameters[5];
  
  // Soldier contribution;
  double offenceContribution, defenceContribution;
  for(vector<Position>::iterator it = (*positionsOfSoldiersOnBoard)[colourOfPlayerToBeEvaluated].begin(); it != (*positionsOfSoldiersOnBoard)[colourOfPlayerToBeEvaluated].end(); ++it) {
    
    int x = it-> x;
    int y = it-> y;

    // Soldier's contribution in offense and defence
    // ? Can be changed to parameter if required
    offenceContribution = (colourOfPlayerToBeEvaluated == int(Colour::black) ?  (numRows - y - 1) : (y));
    defenceContribution = (colourOfPlayerToBeEvaluated == int(Colour::black) ? (y) : (numRows - y - 1));

    // offence defence left wing
    *defenceScoreLeftWing = (*defenceScoreLeftWing) + soldierDefend * defenceContribution * (x < numCols/2);
    *offenceScoreLeftWing = (*offenceScoreLeftWing) + soldierAttack * offenceContribution * (x < numCols/2);

    // offence defence right wing
    *defenceScoreRightWing = (*defenceScoreRightWing) + soldierDefend * defenceContribution * (x >= numCols/2);
    *offenceScoreRightWing = (*offenceScoreRightWing) + soldierAttack * offenceContribution * (x >= numCols/2);
  }
  // Calculating the score because of cannons
  for(vector<Position>::iterator it = (*positionsOfSoldiersOnBoard)[colourOfPlayerToBeEvaluated].begin(); it != (*positionsOfSoldiersOnBoard)[colourOfPlayerToBeEvaluated].end(); ++it){

    int x = it-> x;
    int y = it-> y;

    bool isLeftMostOfHorizontalCannon = ((x + 2) < numCols) && isAllySoldierPresent(board->cannonBoard[y][x+1], colourOfPlayerToBeEvaluated)
                                        && isAllySoldierPresent(board->cannonBoard[y][x+2], colourOfPlayerToBeEvaluated)
                                        && (!((x + 3) < numCols) || !(isAllySoldierPresent(board->cannonBoard[y][x + 3], colourOfPlayerToBeEvaluated)));

    bool isTopLeftMostOfCannon = ((x+2) < numCols) && ((y+2) < numRows) && isAllySoldierPresent(board->cannonBoard[y+1][x+1], colourOfPlayerToBeEvaluated)
                                  && isAllySoldierPresent(board->cannonBoard[y+2][x+2], colourOfPlayerToBeEvaluated)
                                  && (!((y + 3) < numRows && (x + 3) < numCols) || !(isAllySoldierPresent(board->cannonBoard[y+3][x+3], colourOfPlayerToBeEvaluated)));

    bool isTopMostOfVerticalCannon = ((y+2) < numRows) && isAllySoldierPresent(board->cannonBoard[y+1][x], colourOfPlayerToBeEvaluated)
                                      && isAllySoldierPresent(board->cannonBoard[y+2][x], colourOfPlayerToBeEvaluated)
                                      && (!((y + 3) < numRows) || !(isAllySoldierPresent(board->cannonBoard[y+3][x], colourOfPlayerToBeEvaluated)));
    bool isTopRightMostOfCannon = ((x-2) >= 0) && ((y+2) < numRows) && isAllySoldierPresent(board->cannonBoard[y+1][x-1], colourOfPlayerToBeEvaluated)
                                  && isAllySoldierPresent(board->cannonBoard[y + 2][x - 2], colourOfPlayerToBeEvaluated)
                                  && (!((y + 3) < numRows && (x - 3) >= 0) || !(isAllySoldierPresent(board->cannonBoard[y+3][x-3], colourOfPlayerToBeEvaluated)));

    // Currently doing defence offence only
    if(isLeftMostOfHorizontalCannon){
      *defenceScoreLeftWing = (*defenceScoreLeftWing) + parameters[0] * (colourOfPlayerToBeEvaluated == int(Colour::black)? (y) : (numRows - y -1)) * (x + 1 >= numCols/2);
      *defenceScoreRightWing = (*defenceScoreRightWing) + parameters[0] * (colourOfPlayerToBeEvaluated == int(Colour::black)? (y) : (numRows - y -1)) * (x + 1 < numCols/2);
      *defenceScoreLeftWing = (*defenceScoreLeftWing) - max(x - 3, 0);
      *defenceScoreRightWing = (*defenceScoreRightWing) - max(numCols - x - 5, 0); 
    }

    if(isTopMostOfVerticalCannon){
      *offenceScoreLeftWing = (*offenceScoreLeftWing) + parameters[2] * (colourOfPlayerToBeEvaluated == int(Colour::black)? (numRows - (y+1)) * (2 - x%2) : (y + 1) * (1 + x % 2)) * (x < numCols/2);
      *offenceScoreRightWing = (*offenceScoreRightWing) + parameters[2] * (colourOfPlayerToBeEvaluated == int(Colour::black)? (numRows - (y+1)) * (2 - x%2) : (y + 1) * (1 + x % 2)) * (x >= numCols/2);
    }

    if(isTopRightMostOfCannon) {
      if(colourOfPlayerToBeEvaluated == int(Colour::black)) {  
        // *defenceScoreLeftWing = (*defenceScoreLeftWing) + parameters[1] * ((x + y) < numRows ? x + y: numRows + numCols - (x + y) - 1) ;
        *offenceScoreRightWing = (*offenceScoreRightWing) + parameters[1] * ((x + y) < numRows ? x + y: numRows + numCols - (x + y) - 1);
      }
      else {
        *offenceScoreLeftWing = (*offenceScoreLeftWing) + parameters[1] * ((x + y) < numRows ? x + y: numRows + numCols - (x + y) - 1);
        // *defenceScoreRightWing = (*defenceScoreRightWing) + parameters[1]* ((x + y) < numRows ? x + y: numRows + numCols - (x + y) - 1);
      }
    }

    if(isTopLeftMostOfCannon) {
      if(colourOfPlayerToBeEvaluated == int(Colour::black)) {
        *offenceScoreLeftWing = (*offenceScoreLeftWing) + parameters[1] * (numRows - 1 - abs(x - y) - 1);
        // *defenceScoreRightWing = (*defenceScoreRightWing) + parameters[1] * (numRows - 1 - abs(x - y) - 1);
      }
      else {
        // *defenceScoreLeftWing = (*defenceScoreLeftWing) + parameters[1] * (numRows - 1 - abs(x - y) - 1);
        *offenceScoreRightWing = (*offenceScoreRightWing) + parameters[1] * (numRows - 1 - abs(x - y) - 1);
      }
    }
  }
}

double State::getValue(Colour colourOfPlayerToBeEvaluated) {

  parameters = {1.0, 1.0, 1.0, 10000.0, 3.0, 2.0};
  // Get the black and white soldiers
  int blackSoldiers = this->currentBoard.positionsOfSoldiersOnBoard[0].size();
  int whiteSoldiers = this->currentBoard.positionsOfSoldiersOnBoard[1].size();
  int blackTownhalls = this->currentBoard.numberOfBlackTownhalls();
  int whiteTownhalls = this->currentBoard.numberOfWhiteTownhalls();

  // ? Right left with respect to our screen, not with respect to rotation of board
  double defenceScoreRightWingBlack = 0.0; 
  double offenceScoreRightWingBlack = 0.0;
  double defenceScoreLeftWingBlack = 0.0;
  double offenceScoreLeftWingBlack = 0.0;

  //// vector<int> parameters;

  ////int differenceOfSoldier;

  // Soldier count
  int numberOfSelfSoldiers = colourOfPlayerToBeEvaluated == Colour::black ? blackSoldiers : whiteSoldiers;
  int numberOfOpponentSoldiers = colourOfPlayerToBeEvaluated == Colour::black ? whiteSoldiers : blackSoldiers;

  // Black score
  // Horizontal cannon
  // TODO: correct this for 10 X 10
  // ! Kept like this to reciprocate results
  parameters[0] *= ((16 - numberOfSelfSoldiers)/ 4);
  // Diagonal cannon
  parameters[1] *= (numberOfOpponentSoldiers/4 + 1);
  // Vertical cannon
  parameters[2] *= (numberOfOpponentSoldiers/4 + 1);
  // parameters = {(16 - numberOfSelfSoldiers)/4, numberOfOpponentSoldiers/4 + 1, numberOfOpponentSoldiers/4 + 1};
  this->calculateStateScoreParameters(0, &defenceScoreRightWingBlack, &offenceScoreRightWingBlack,
                                      &defenceScoreLeftWingBlack, &offenceScoreLeftWingBlack);

  // TODO: can add mobility
  // White score
  double defenceScoreRightWingWhite = 0.0; 
  double offenceScoreRightWingWhite = 0.0;
  double defenceScoreLeftWingWhite = 0.0;
  double offenceScoreLeftWingWhite = 0.0;

  this->calculateStateScoreParameters(1, &defenceScoreRightWingWhite, &offenceScoreRightWingWhite,
                                      &defenceScoreLeftWingWhite, &offenceScoreLeftWingWhite);

  // Overall score
  double value;
  double score = offenceScoreLeftWingBlack + defenceScoreLeftWingBlack 
  - defenceScoreLeftWingWhite - offenceScoreLeftWingWhite 
  + defenceScoreRightWingBlack + offenceScoreRightWingBlack 
  - offenceScoreRightWingWhite - defenceScoreRightWingWhite;
  
  // Townhall score 
  double townhallScore = parameters[3];

  // TODO: correct this if
  if(blackTownhalls > whiteTownhalls || (blackTownhalls == whiteTownhalls && colourOfPlayerToBeEvaluated == Colour::black)){

    value = (blackSoldiers - whiteSoldiers) + townhallScore * (blackTownhalls - whiteTownhalls) + 0 * (defenceScoreLeftWingBlack - offenceScoreLeftWingWhite) + 1 * score;
  }
  else {
    value = (blackSoldiers - whiteSoldiers) + townhallScore * (blackTownhalls - whiteTownhalls) + 1 * (score) + 0 * (offenceScoreLeftWingBlack - defenceScoreLeftWingWhite);
  }

  // Minimum number of townhalls
  int minimumTownhalls = (this->currentBoard.getColumns() / 2) - 1;

  if(whiteTownhalls < minimumTownhalls) {
      value = 100000.0;
  }
  if(blackTownhalls < minimumTownhalls) {
    value = -100000.0;
  }
  if(colourOfPlayerToBeEvaluated == Colour::black)
      return value;
  else
  {
      return -value;
  }
}
