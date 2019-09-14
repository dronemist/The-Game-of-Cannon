#ifndef SEARCH_H
#define SEARCH_H
#include <string>
#include "state.h"

/// This function does minimax search and returns the best possible move at current level
/// - Parameters:
///   - currentDepth: the depth of the current node
///   - currentState: the pointer to the current state
///   - isMax: if the current node is a max node
///   - ply: the ply upto which search is to be performed
///   - optimalMove: move for most optimal play
///   - alpha
///   - beta
int minimax(int, State *, bool, int, std::string &, int, int, Colour);

/// This function performs iterative deepening minimax search
/// - Parameters:
///   - startState: the pointer to the current state
///   - maxPly: the ply upto which search is to be performed
///   - colour: the colour of current node
void iterativeDeepening(State *startState, int maxPly, Colour colour);
#endif