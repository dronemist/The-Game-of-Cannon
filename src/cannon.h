#ifndef CANNON_H
#define CANNON_H
#include <vector>
// DOUBT: Should we add it to the same file?
#include "position.h"
#include "board.h"
#include "piece.h"

class Cannon: public Piece
{
private:
    Position startPoint;
    Position endPoint;
public:
    Cannon(Position, Position, Colour);
    /// This function returns the allowed move of the cannon
    // DOUBT: Is cannon shot a part of allowed moves
    std::vector<std::string> getAllowedMoves(Board &);
    std::vector<std::string> getAllowedCannonMoves(Board &);
    /// This functions move the piece to the new starting position
    void movePiece(Position);
    /// This function returns the type of piece
    PieceType getType();
};

#endif
