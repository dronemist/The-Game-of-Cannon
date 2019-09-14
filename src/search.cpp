#include <iostream>
#include<algorithm>
#include "search.h"
#include <unordered_map>
#define loop(i, start, end) for(int i = start; i < end; i++)

using namespace std;

unordered_map<string, int> cache;


/// This function does minimax search and returns the best possible move at current level
/// - Parameters:
///   - currentDepth: the depth of the current node
///   - currentState: the pointer to the current state
///   - isMax: if the current node is a max node
///   - ply: the ply upto which search is to be performed
///   - optimalMove: move for most optimal play
///   - colour: colour of root node

// bool compareStates(Colour colour, State* state_1, State* state_2){
//   return state_1->getValue(colour) > state_2->getValue(colour);
// }
int count = 0;
struct myComp {
  Colour colour;
  bool isMax;
  myComp(Colour initialColour, bool isMax){
    colour = initialColour;
    this->isMax = isMax;
  }
  bool operator() (State* state_1, State* state_2) {
    if(isMax) {
        return cache[state_1->getStringValue()] > cache[state_2->getStringValue()];
        // return state_1->getValue(this->colour) > state_2->getValue(this->colour);
    } else {  
        return cache[state_1->getStringValue()] < cache[state_2->getStringValue()];
        // return state_1->getValue(this->colour) < state_2->getValue(this->colour);
    }
  }
};

int minimax(int currentDepth, State *currentState, bool isMax, int ply, string &optimalMove, int alpha, int beta, Colour colour) {

    string currentStringValue = currentState->getStringValue();
    if(currentDepth == ply) {
        int value = currentState->getValue(colour);
        cache[currentStringValue] = value;
        return value;
        // NOTE: What if ply = 1?
    }
    vector<State*> nextStates;
    currentState->expand(nextStates);
    if (nextStates.size() == 0) {
        int value = currentState->getValue(colour);
        cache[currentStringValue] = value;
        return value;
    }
    myComp myCompInstance = myComp(colour, isMax);
    // Sorts states in ascending order
    // if(currentDepth != ply - 1)
    //     sort(nextStates.begin(), nextStates.end(), myCompInstance);
    if(isMax) {
        int best = INT32_MIN;
        loop(i, 0, nextStates.size()) {
            // calculating min values of child of max
            int minVal = minimax(currentDepth + 1, nextStates[i], false, ply, optimalMove, alpha, beta, colour);
            alpha = max(alpha, minVal);
            if(alpha >= beta) {
                ::count += currentDepth;
                delete nextStates[i];
                cache[currentStringValue] = minVal;
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
        cache[currentStringValue] = best;
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
                ::count += currentDepth;
                cache[currentStringValue] = maxVal;
                return maxVal;
            }
            best = min(best, maxVal);
        }
        cache[currentStringValue] = best;
        return best;
    }
}

void iterativeDeepening(State *startState, int maxPly, Colour colour) {
    cache = {};
    string optimalMove = "";
    loop(i, 1, 5) {
        minimax(0, startState, true, i, optimalMove, INT32_MIN, INT32_MAX, colour);
    }
    cout<<::count;
    cout<<endl<<optimalMove<<endl;  
}
