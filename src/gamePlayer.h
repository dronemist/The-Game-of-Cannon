#ifndef GAMEPLAYER_H
#define GAMEPLAYER_H
#include "search.h"
class GamePlayer
{
private:
   int ply;
public:
    State *currentState;
    GamePlayer(Colour, int = 4);
    std::string play();
};

#endif