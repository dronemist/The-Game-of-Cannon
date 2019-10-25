#include <iostream>
#include<algorithm>
#include "search.h"
#define loop(i, start, end) for(int i = start; i < end; i++)

using namespace std;

struct myComp {
  // Colour colour;
  Colour colourOfPlayerToBeEvaluated;
  Colour colourOfMovingPlayer;
  bool isMax;
  myComp(Colour colourOfPlayerToBeEvaluated, Colour colourOfMovingPlayer, bool isMax){
    this->colourOfPlayerToBeEvaluated = colourOfPlayerToBeEvaluated;
    this->colourOfMovingPlayer = colourOfMovingPlayer;
    this->isMax = isMax;
  }
  bool operator() (State* state_1, State* state_2){
      if(this->isMax) {
        return state_1->getValue(colourOfPlayerToBeEvaluated, colourOfMovingPlayer) > state_2->getValue(colourOfPlayerToBeEvaluated, colourOfMovingPlayer);
      } else {
        return state_1->getValue(colourOfPlayerToBeEvaluated, colourOfMovingPlayer) < state_2->getValue(colourOfPlayerToBeEvaluated, colourOfMovingPlayer);
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
///   - colour: colour of root node
int minimax(int currentDepth, State *currentState, bool isMax, int ply, string &optimalMove, int alpha, int beta, Colour colour) {

    Colour oppositeOfColour = (colour == Colour::black) ? Colour::white : Colour::black;
    Colour colourOfMovingPlayer = (currentDepth % 2 == 0) ? colour : oppositeOfColour;

    if(currentDepth == ply) {
        return currentState->getValue(colour, colourOfMovingPlayer);
    }
    // Don't consider moves if townhall limit reached
    bool gameOver = (colour == Colour::black && currentState->currentBoard.numberOfWhiteTownhalls() == 2)
    || (colour == Colour::white && currentState->currentBoard.numberOfBlackTownhalls() == 2);
    if(gameOver) {
        return currentState->getValue(colour, colourOfMovingPlayer);
    }
    vector<State*> nextStates;
    currentState->expand(nextStates);
    if (nextStates.size() == 0) {
      return currentState->getValue(colour, colourOfMovingPlayer);
    }

    myComp myCompInstance = myComp(colour, colourOfMovingPlayer, isMax);
    // Sorts states in ascending and descending order
    if(currentDepth + 1 != ply)
        sort(nextStates.begin(), nextStates.end(), myCompInstance);

    if(isMax) {
        int best = INT32_MIN;
        loop(i, 0, nextStates.size()) {
            // calculating min values of child of max
            int minVal = minimax(currentDepth + 1, nextStates[i], false, ply, optimalMove, alpha, beta, colour);
            alpha = max(alpha, minVal);
            if(alpha >= beta) {
                delete nextStates[i];
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
        int best = INT32_MAX;
        loop(i, 0, nextStates.size()) {
            // calculating max values of child of min
            int maxVal = minimax(currentDepth + 1, nextStates[i], true, ply, optimalMove, alpha, beta, colour);
            // deleting state pointer
            delete nextStates[i];
            beta = min(beta, maxVal);
            if(alpha >= beta) {
                return maxVal;
            }
            best = min(best, maxVal);
        }
        return best;
    }
}
