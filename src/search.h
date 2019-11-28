#ifndef SEARCH_H
#define SEARCH_H
#include <string>
#include "state.h"
#include <climits>

/// This function does minimax search and returns the best possible move at current level
/// - Parameters:
///   - currentDepth: the depth of the current node
///   - currentState: the pointer to the current state
///   - isMax: if the current node is a max node
///   - ply: the ply upto which search is to be performed
///   - optimalMove: move for most optimal play
///   - alpha
///   - beta
double minimax(int, State *, bool, int, std::string &, double, double, Colour, bool);
#endif