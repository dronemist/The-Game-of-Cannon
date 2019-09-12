#include <iostream>
#include<algorithm>
#include "search.h"
#define loop(i, start, end) for(int i = start; i < end; i++)

using namespace std;

/// This function does minimax search and returns the best possible move at current level
/// - Parameters:
///   - currentDepth: the depth of the current node
///   - currentState: the pointer to the current state
///   - isMax: if the current node is a max node
///   - ply: the ply upto which search is to be performed
///   - optimalMove: move for most optimal play
///   - colour: colour of root node

bool compareStates(Colour colour, State* state_1, State* state_2){
  return state_1->getValue(colour) > state_2->getValue(colour);
}

struct myComp{
  Colour colour;
  myComp(Colour initialColour){
    colour = initialColour;
  }
  bool operator() (State* state_1, State* state_2){
    return state_1->getValue(colour) < state_2->getValue(colour);
  }
};

int minimax(int currentDepth, State *currentState, bool isMax, int ply, string &optimalMove, int alpha, int beta, Colour colour) {

    if(currentDepth == ply) {
        return currentState->getValue(colour); //NOTE: What if ply = 1?
    }


    vector<State*> nextStates = currentState->expand();
    if (nextStates.size() == 0) {
      return currentState->getValue(colour);
    }

    myComp myCompInstance = myComp(colour);

    sort(nextStates.begin(), nextStates.end(), myCompInstance); //Sorts states in ascending order
    if(isMax){
        reverse(nextStates.begin(), nextStates.end());  //NOTE: Check if we have to reverse for Max or Min
    }


    if(currentDepth == 1){
      loop(i, 0, nextStates.size()){
        cout<<nextStates[i]->moveFromPreviousState<<endl;
      }
    }
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
            if(minVal > best && currentDepth == 1) {
                best = minVal;
                optimalMove = nextStates[i]->moveFromPreviousState;
            } else {
                best = max(best, minVal);
            }
            cout<<"depth = "<<currentDepth + 1 <<" "<<minVal<<" ";
            delete nextStates[i];
        }
        cout<<endl;
        // cout<<endl<<best<<endl;
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
            cout<<"depth = "<<currentDepth + 1 <<" "<<maxVal<<" ";
        }
        // cout<<endl<<best<<endl;
        cout<<endl;
        return best;
    }
}
