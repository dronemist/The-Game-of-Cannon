#ifndef SOLDIER_H
#define SOLDIER_H
#include <vector>
// DOUBT: Should we add it to the same file?
#include "position.h"
#include "board.h"
#include "piece.h"
class Soldier: public Piece
{
private:
    /// Current position of the soldier
    Position position;
public:
    Soldier(Position, Colour);
    /// This function returns the allowed moves of the soldier
    std::vector<Position> getAllowedMoves(Board &currentBoard);
    /// This functions move the piece to the new position
    void movePiece(Position);
    /// This function returns the type of piece
    virtual PieceType getType();
    
};

#endif