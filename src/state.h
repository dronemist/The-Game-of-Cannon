#ifndef STATE_H
#define STATE_H
#include <string>
#include "board.h"

class State
{
public:
    State *previousState;
    Board currentBoard;
    /// The move that brought the state from previous state to current state
    std::string moveFromPreviousState;
    std::vector<State*> expand(); 
    /// constructor;
    State(int = 8, int = 8, Colour = Colour::black);
    /// This function takes the move
    void makeMove(std::string, Board &);
    /// Colour of the player whose move it is;
    Colour colourOfCurrentPlayer;
    void removePositonFromBoard(Board &, int , int);
    // value / evaluation of the state
    int getValue(Colour);
};
#endif