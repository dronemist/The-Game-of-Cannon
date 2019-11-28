#ifndef PIECE_H
#define PIECE_H
#include <vector>
#include <string>
#include "position.h"
#include "board.h"
class Board;
/// Piece class
class Piece
{
protected:
    Colour colour;
public:
    /// This function returns the allowed move of the cannon
    /// - Parameters
    ///   - currentBoard: the orientation of the current board
    virtual void getAllowedMoves(Board &, Position*, std::vector<std::string> &) {
        // Do nothing!
    }
    /// This function returns the type of piece
    virtual PieceType getType() {
        return PieceType::null;
    };
    Colour getColour() {
        return this->colour;
    };

};

#endif
