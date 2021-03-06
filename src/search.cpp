#include <iostream>
#include <algorithm>
#include "search.h"
#define loop(i, start, end) for(int i = start; i < end; i++)

using namespace std;

struct myComp {
  // Colour colour;
  Colour colourOfPlayerToBeEvaluated;
  bool isMax;
  myComp(Colour colourOfPlayerToBeEvaluated, bool isMax){
    this->colourOfPlayerToBeEvaluated = colourOfPlayerToBeEvaluated;
    this->isMax = isMax;
  }
  bool operator() (State* state_1, State* state_2){
      if(this->isMax) {
        return state_1->getValue(colourOfPlayerToBeEvaluated) > state_2->getValue(colourOfPlayerToBeEvaluated);
      } else {
        return state_1->getValue(colourOfPlayerToBeEvaluated) < state_2->getValue(colourOfPlayerToBeEvaluated);
      }
  }
};

/// This function does minimax search and returns the best possible move at current level
/// - Parameters:
///   - currentDepth: the depth of the current node
///   - currentState: the pointer to the current state
///   - isMax: if the current node is a max node
///   - ply: the ply upto which search is to be performed
///   - optimalMove: move for most optimal play
///   - alpha 
///   - beta
///   - colour: colour of root node
///   - passingShotAllowed
double minimax(int currentDepth, State *currentState, bool isMax, int ply, string &optimalMove, double alpha, double beta, Colour colour, bool passingShotAllowed) {


    Colour oppositeOfColour = (colour == Colour::black) ? Colour::white : Colour::black;
    Colour colourOfMovingPlayer = (currentDepth % 2 == 0) ? colour : oppositeOfColour;

    if(currentDepth == ply) {
        return currentState->getValue(colour);
    }

    

    // Minimum number of townhalls allowed
    int minimumTownhalls = (currentState->currentBoard.getColumns() / 2) - 2;

    // Don't consider moves if townhall limit reached or soldiers finished
    bool gameOver = (currentState->currentBoard.numberOfWhiteTownhalls() <= minimumTownhalls)
    || (currentState->currentBoard.numberOfBlackTownhalls() <= minimumTownhalls)
    || (currentState->currentBoard.positionsOfSoldiersOnBoard[0].size() == 0)
    || (currentState->currentBoard.positionsOfSoldiersOnBoard[1].size() == 0);
    if(gameOver) {
        return currentState->getValue(colour);
    }
    
  

    vector<State*> nextStates;
    currentState->expand(nextStates, passingShotAllowed);

    

    if (nextStates.size() == 0) {
      return currentState->getValue(colour);
    }

    myComp myCompInstance = myComp(colour, isMax);
    // Sorts states in ascending and descending order
    if(currentDepth + 1 != ply)
        sort(nextStates.begin(), nextStates.end(), myCompInstance);

    if(isMax) {
        double best = -(__DBL_MAX__ - 1);
        loop(i, 0, nextStates.size()) {
            // calculating min values of child of max
            double minVal = minimax(currentDepth + 1, nextStates[i], false, ply, optimalMove, alpha, beta, colour, passingShotAllowed);
            alpha = max(alpha, minVal);
            if(alpha >= beta) {
                // delete nextStates[i];
                loop(j, i, nextStates.size()){
                    delete nextStates[j];
                }
                return minVal;
            }
            if(minVal > best && currentDepth == 0) {
                best = minVal;
                optimalMove = nextStates[i]->moveFromPreviousState;
            } else {
                best = max(best, minVal);
            }
            delete nextStates[i];
        }
        return best;
    } else {
        double best = __DBL_MAX__;
        loop(i, 0, nextStates.size()) {
            // calculating max values of child of min
            double maxVal = minimax(currentDepth + 1, nextStates[i], true, ply, optimalMove, alpha, beta, colour, passingShotAllowed);
            beta = min(beta, maxVal);
            if(alpha >= beta) {
                loop(j, i, nextStates.size()){
                    delete nextStates[j];
                }
                return maxVal;
            }
            best = min(best, maxVal);
            // deleting state pointer
            delete nextStates[i];
        }
        return best;
    }
}
