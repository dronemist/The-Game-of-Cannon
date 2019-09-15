#ifndef GAMEPLAYER_H
#define GAMEPLAYER_H
#include "search.h"
class GamePlayer
{
private:
   int ply;
   int temp;
public:
    State *currentState;
    GamePlayer(Colour, int = 4, int = 8, int = 8);
    Colour colourOfPlayer;
    std::string play();
};

#endif