#ifndef PIECE_H
#define PIECE_H
#include <vector>
#include <string>
// DOUBT: Should we add it to the same file?
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
    virtual std::vector<std::string> getAllowedMoves(Board &, Position*) {
        return std::vector<std::string>();
    }
    /// This functions move the piece to the new starting position
    // virtual void movePiece(Position);
    /// This function returns the type of piece
    virtual PieceType getType() {
        return PieceType::null;
    };
    Colour getColour() {
        return this->colour;
    };

};

#endif
