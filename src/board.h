#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include<list>
#include "cannon.h"
#include "soldier.h"
#include "townhall.h"
class Piece;

// struct boardPieceAndItsPositionInList{
//   Piece* piece;
//   list<Position>::iterator it;
// };

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
    std::list<Position> positionsOfSoldiersOnBoard;
    /// Constructor
    Board(int = 8, int = 8);
    /// Temp function to print board
    void printBoard();
    /// returns the number of rows
    int getRows();
    /// returns the number of columns
    int getColumns();
};
#endif
