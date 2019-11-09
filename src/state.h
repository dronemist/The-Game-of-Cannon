#ifndef STATE_H
#define STATE_H
#include <string>
#include "board.h"

extern std::vector<double> parameters;

// TODO: is static correct?
static std::vector<double> tempFeature;
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

    /// Calculates defence and offence score parameters
    void calculateStateScoreParameters(int, double*, double*,
                                      double*, double*, std::vector<double> &);
    /// Calculates Minimum TownHall Distance Heuristic for soldiers
    double getMinimumTownHallDistanceHeuristicValue(int, double);
    // value / evaluation of the state
    double getValue(Colour, std::vector<double> & = tempFeature);
};
#endif
