#ifndef TOWNHALL_H
#define TOWNHALL_H
#include <vector>
// DOUBT: Should we add it to the same file?
#include "position.h"
#include "board.h"
#include "piece.h"
class Townhall: public Piece
{
private:
    /// Current position of the townhall
    Position position;
public:
    Townhall(Colour);
    /// This function returns the type of piece
    PieceType getType();
};

#endif
