#ifndef STATE_H
#define STATE_H
#include <string>
#include "board.h"
class state
{
public:
    state *previousState;
    Board currentBoard;
    /// The move that brought the state from previous state to current state
    std::string moveFromPreviousState;
    std::vector<state*> expand; 
};
#endif