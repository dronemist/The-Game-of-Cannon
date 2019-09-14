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
    void expand(std::vector<State*> &);
    /// constructor;
    State(int = 8, int = 8, Colour = Colour::black);
    /// This function takes the move
    void makeMove(std::string, Board &);
    /// Colour of the player whose move it is;
    Colour colourOfCurrentPlayer;
    void removePositonFromBoard(Board &, int , int);

    ///Calculates defence and offence score parameters
    void calculateStateScoreParameters(int, int*, int*,
                                      int*, int*,
                                      int*, int*, std::vector<int> &);
    // value / evaluation of the state
    int getValue(Colour, Colour);
};
#endif
