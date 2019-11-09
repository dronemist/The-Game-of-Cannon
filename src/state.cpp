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
* 6 : minimumTownHallHeuristic
*/
vector<double> parameters = {1.0, 1.0, 1.0, 10000.0, 3.0, 2.0, 20}; 
//vector<double> parameters = {0.742608, 0.609946, 0.758162, 10000, 3.10526, 1.97368};


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
                                        double* defenceScoreLeftWing, double* offenceScoreLeftWing, vector<double> &featureVals) {
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

    // Feature values
    featureVals[4] += offenceContribution; 
    featureVals[5] += defenceContribution;
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
    if(isLeftMostOfHorizontalCannon) {
      *defenceScoreLeftWing = (*defenceScoreLeftWing) + parameters[0] * (colourOfPlayerToBeEvaluated == int(Colour::black)? (y) : (numRows - y -1)) * (x + 1 >= numCols/2);
      *defenceScoreRightWing = (*defenceScoreRightWing) + parameters[0] * (colourOfPlayerToBeEvaluated == int(Colour::black)? (y) : (numRows - y -1)) * (x + 1 < numCols/2);
      // TODO: figure this out
      *defenceScoreLeftWing = (*defenceScoreLeftWing) - max(x - 3, 0);
      *defenceScoreRightWing = (*defenceScoreRightWing) - max(numCols - x - 5, 0); 
      
      // Assigning feature value
      featureVals[0] += (colourOfPlayerToBeEvaluated == int(Colour::black)? (y) : (numRows - y -1));
    }

    if(isTopMostOfVerticalCannon) {
      // Whether townhall is present in those x coordinates
      bool isTownhallPresent = false;
      if(colourOfPlayerToBeEvaluated == int(Colour::black)) {
        if(this->currentBoard.cannonBoard[0][x] != nullptr
          && this->currentBoard.cannonBoard[0][x]->getType() == PieceType::townhall) {
            isTownhallPresent = true;
        }
      } else if (colourOfPlayerToBeEvaluated == int(Colour::white)) {
        if(this->currentBoard.cannonBoard[numRows - 1][x] != nullptr
          && this->currentBoard.cannonBoard[numRows - 1][x]->getType() == PieceType::townhall) {
            isTownhallPresent = true;
        }
      }
      *offenceScoreLeftWing = (*offenceScoreLeftWing) + parameters[2] * (colourOfPlayerToBeEvaluated == int(Colour::black)? (numRows - (y+1)) * (2 - (!isTownhallPresent)) : (y + 1) * (1 + isTownhallPresent)) * (x < numCols/2);
      *offenceScoreRightWing = (*offenceScoreRightWing) + parameters[2] * (colourOfPlayerToBeEvaluated == int(Colour::black)? (numRows - (y+1)) * (2 - (!isTownhallPresent)) : (y + 1) * (1 + isTownhallPresent)) * (x >= numCols/2);

      // Assigning feature value
      featureVals[2] += (colourOfPlayerToBeEvaluated == int(Colour::black)? (numRows - (y+1)) * (2 - (!isTownhallPresent)) : (y + 1) * (1 + isTownhallPresent));
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
      featureVals[1] += ((x + y) < numRows ? x + y: numRows + numCols - (x + y) - 1);
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
      featureVals[1] += (numRows - 1 - abs(x - y) - 1);
    }
  }
}


double State::getMinimumTownHallDistanceHeuristicValue(int colourOfPlayerToBeEvaluated, double weight) {

  int numTownhalls = this->currentBoard.getColumns() / 2;
  vector<int> townHallHeuristicValues(numTownhalls, INT32_MAX);

  int numRows = this->currentBoard.getRows();
  int numRowsMinusOne = numRows - 1;

  // Aliasing the positionOfSoldiersOnBoard variable
  vector<Position> & positionOfSoldiersOnBoard = this->currentBoard.positionsOfSoldiersOnBoard[colourOfPlayerToBeEvaluated];
  int numSoldiers = positionOfSoldiersOnBoard.size();

  loop(i, 0, numSoldiers) {
    int soldierHorizontalPosition = positionOfSoldiersOnBoard[i].x;
    int soldierVerticalPosition = positionOfSoldiersOnBoard[i].y;
    int spanLeftLimit = 0;
    int spanRightLimit = 0;

    if (colourOfPlayerToBeEvaluated == int(Colour::black)) { 
      // If colour of player is black
      
      spanLeftLimit = soldierHorizontalPosition - soldierVerticalPosition;
      spanRightLimit = soldierHorizontalPosition + soldierVerticalPosition; 

      // Making left limit even since white townhalls at even position
      spanLeftLimit = spanLeftLimit % 2 == 0 ? spanLeftLimit : spanLeftLimit + 1; 
      spanLeftLimit = max(spanLeftLimit, 0);
      spanRightLimit = min(spanRightLimit, this->currentBoard.getColumns());
      
      // Looking at white townhalls
      for(int i=spanLeftLimit; i<spanRightLimit; i+=2) {
        bool doesTownHallExist = this->currentBoard.cannonBoard[0][i] != nullptr 
                              && this->currentBoard.cannonBoard[0][i]->getType() == PieceType::townhall;

        if (doesTownHallExist) {
          townHallHeuristicValues[i/2] = min(townHallHeuristicValues[i/2], soldierVerticalPosition);
        }

      }


    }
    else { 
      // If colour of player is white

      spanLeftLimit = soldierHorizontalPosition - (numRowsMinusOne - soldierVerticalPosition);
      spanRightLimit = soldierHorizontalPosition + (numRowsMinusOne - soldierVerticalPosition); 

      // Making left limit odd since black townhalls at odd positions
      spanLeftLimit = spanLeftLimit % 2 == 1 ? spanLeftLimit : spanLeftLimit + 1; 
      spanLeftLimit = max(spanLeftLimit, 1);
      spanRightLimit = min(spanRightLimit, this->currentBoard.getColumns());
      
      // Looking at white townhalls
      for(int i=spanLeftLimit; i<spanRightLimit; i+=2){
        bool doesTownHallExist = this->currentBoard.cannonBoard[numRowsMinusOne][i] != nullptr 
                              && this->currentBoard.cannonBoard[numRowsMinusOne][i]->getType() == PieceType::townhall;

        if (doesTownHallExist){
          townHallHeuristicValues[i/2] = min(townHallHeuristicValues[i/2], numRowsMinusOne - soldierVerticalPosition);
        }

      }

    }

  }

  double score = 0;

  loop(i, 0, numTownhalls){
    bool toCountValue = townHallHeuristicValues[i] != INT32_MAX;

    if(toCountValue){
      double value = numRowsMinusOne - townHallHeuristicValues[i];
      score = max(value, score);
      // score += value*value*weight;
    }
  } 
  score = score * weight;
  return score;
}




double State::getValue(Colour colourOfPlayerToBeEvaluated, vector<double> &features) {

  features.clear();
  vector<double> parametersTemp = parameters;
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
  // Dimensions of board
  int numCols = this->currentBoard.getColumns();  
  int numRows = this->currentBoard.getRows();

  // Soldier count
  int numberOfSelfSoldiers = colourOfPlayerToBeEvaluated == Colour::black ? blackSoldiers : whiteSoldiers;
  int numberOfOpponentSoldiers = colourOfPlayerToBeEvaluated == Colour::black ? whiteSoldiers : blackSoldiers;
  int maxSoldiersOneSide = 3 * ( numCols/ 2);


  // Black score
  vector<double> blackFeatures(parametersTemp.size(), 0.0);
  // Horizontal cannon
  // TODO: correct this for 10 X 10
  // ! Kept like this to reciprocate results
  parameters[0] *= ((maxSoldiersOneSide + (numCols/2) - numberOfSelfSoldiers)/ (numCols/2));
  // Diagonal cannon
  parameters[1] *= (numberOfOpponentSoldiers/(numCols/2) + 1);
  // Vertical cannon
  parameters[2] *= (numberOfOpponentSoldiers/(numCols/2) + 1);
  // parameters = {(16 - numberOfSelfSoldiers)/4, numberOfOpponentSoldiers/4 + 1, numberOfOpponentSoldiers/4 + 1};
  this->calculateStateScoreParameters(0, &defenceScoreRightWingBlack, &offenceScoreRightWingBlack,
                                      &defenceScoreLeftWingBlack, &offenceScoreLeftWingBlack, blackFeatures);

  blackFeatures[3] = blackTownhalls;

  // TODO: can add mobility
  // White score
  vector<double> whiteFeatures(parametersTemp.size(), 0.0);
  double defenceScoreRightWingWhite = 0.0; 
  double offenceScoreRightWingWhite = 0.0;
  double defenceScoreLeftWingWhite = 0.0;
  double offenceScoreLeftWingWhite = 0.0;

  this->calculateStateScoreParameters(1, &defenceScoreRightWingWhite, &offenceScoreRightWingWhite,
                                      &defenceScoreLeftWingWhite, &offenceScoreLeftWingWhite, whiteFeatures);

  whiteFeatures[3] = whiteTownhalls;
  // Overall score
  double value;
  double score = offenceScoreLeftWingBlack + defenceScoreLeftWingBlack 
  - defenceScoreLeftWingWhite - offenceScoreLeftWingWhite 
  + defenceScoreRightWingBlack + offenceScoreRightWingBlack 
  - offenceScoreRightWingWhite - defenceScoreRightWingWhite;
  
  // Calculating the feature values
  loop(i, 0, whiteFeatures.size()) {
    if(colourOfPlayerToBeEvaluated == Colour::black) {
      features.push_back(blackFeatures[i] - whiteFeatures[i]);
    } else {
      features.push_back(whiteFeatures[i] - blackFeatures[i]);
    }
  }

  // Townhall score 
  double townhallScore = parameters[3];


  if (numberOfSelfSoldiers + numberOfOpponentSoldiers <= maxSoldiersOneSide) {
    double minimumTownHallDistanceHeuristicBlack = getMinimumTownHallDistanceHeuristicValue(0, parameters[6]);
    double minimumTownHallDistanceHeuristicWhite = getMinimumTownHallDistanceHeuristicValue(1, parameters[6]);

    // minimumTownHallDistanceHeuristicBlack = minimumTownHallDistanceHeuristicBlack >= parameters[6] * numRows/2 ? minimumTownHallDistanceHeuristicBlack : 0;

    // minimumTownHallDistanceHeuristicWhite = minimumTownHallDistanceHeuristicWhite >= parameters[6] * numRows/2 ? minimumTownHallDistanceHeuristicWhite : 0;

    score += minimumTownHallDistanceHeuristicBlack - minimumTownHallDistanceHeuristicWhite;
  }


  
  // If no soldiers are left
  if(this->currentBoard.positionsOfSoldiersOnBoard[0].size() == 0) {
    blackTownhalls--;
  } else if(this->currentBoard.positionsOfSoldiersOnBoard[1].size() == 0) {
    whiteTownhalls--;
  }
  
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
    if(blackTownhalls == minimumTownhalls) {
      value = 80000.0;
    } else {
      value = 100000.0;
    }
  }
  if(blackTownhalls < minimumTownhalls) {
    if(whiteTownhalls == minimumTownhalls) {
      value = -80000.0;
    } else {
      value = -100000.0;
    }
  }
  // Restoring value
  parameters = parametersTemp;
  if(colourOfPlayerToBeEvaluated == Colour::black)
      return value;
  else
  {
      return -value;
  }
}
