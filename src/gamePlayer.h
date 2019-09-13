#ifndef GAMEPLAYER_H
#define GAMEPLAYER_H
#include "search.h"
class GamePlayer
{
private:
   int ply;
public:
    State *currentState;
    GamePlayer(Colour, int = 5, int = 8, int = 8);
    std::string play();
};

#endif