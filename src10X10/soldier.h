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
public:
    // Soldier(Position, Colour);
    Soldier(Colour);
    /// This function returns the allowed moves of the soldier
    void getAllowedMoves(Board &, Position*, std::vector<std::string> &);

    /// Returns all the moves of canons in the board consisting of that soldieer
    void getAllowedCannonMoves(Board &, Position*, std::vector<std::string> &);
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
    /// This is function to check if opponent soldier present
    bool isOpponentSoldierPresent(Piece *);
};

#endif
