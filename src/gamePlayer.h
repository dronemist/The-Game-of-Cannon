#ifndef GAMEPLAYER_H
#define GAMEPLAYER_H
#include "search.h"
class GamePlayer
{
private:
public:
    State *currentState;
    int ply;
    GamePlayer(Colour, int = 4, int = 8, int = 8);
    std::string play(bool = false);
};

#endif