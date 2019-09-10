#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include "cannon.h"
#include "soldier.h"
#include "townhall.h"
class Piece;
class Board
{
private:
    // DOUBT: in board will all three position point to cannon?
    /// Number of rows
    int rows;
    /// Number of columns
    int columns;
    
public:
    /// The current board
    std::vector<std::vector<Piece*>> cannonBoard;
    /// The list of pieces
    std::vector<Piece*> listOfPieces;
    /// Constructor
    Board(int = 8, int = 8);
    /// Temp function to print board
    void printBoard();
};
#endif