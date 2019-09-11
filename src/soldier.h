#ifndef SOLDIER_H
#define SOLDIER_H
#include <vector>
#include <string>
// DOUBT: Should we add it to the same file?
#include "position.h"
#include "board.h"
#include "piece.h"
class Soldier: public Piece
{
private:
    /// Current position of the soldier
    // Position position;
public:
    // Soldier(Position, Colour);
    Soldier(Colour);
    /// This function returns the allowed moves of the soldier
    std::vector<std::string> getAllowedMoves(Board &, Position*);

    /// Returns all the moves of canons in the board consisting of that soldieer
    std::vector<std::string> getAllowedCannonMoves(Board &, Position*);
    /// This functions move the piece to the new position
    // void movePiece(Position);
    /// This function returns the type of piece
    PieceType getType();

    /// To check if soldier of same color present
    bool isAllySoldierPresent(Piece* ptr);

    /// To convert the movement of a soldier/cannon to its string
    std::string moveEncoding(int, int , int , int);

    /// To convert cannon Shot of a soldier to its string
    std::string cannonShotEncoding(int, int, int, int);

    /// To check if no piece present at that position
    bool isPositionEmpty(Piece *);

    /// This function tells if an opponent is present
    bool isOpponentPresent(Piece *);
    /// This function tells if soldier can move to ptr
    bool canMoveToPosition(Piece *);
};

#endif
