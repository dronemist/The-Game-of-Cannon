#include <iostream>
#include "gamePlayer.h"

using namespace std;

int main() {
    string move = "";
    GamePlayer g1(Colour::black, 4);
    GamePlayer g2(Colour::white, 5);
    while (true)
    {
        move = g1.play();
        g2.currentState->makeMove(move, g2.currentState->currentBoard);
        move = g2.play();
    }
}