#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <list>
#include "soldier.h"
#include "townhall.h"
class Piece;

class Board
{
private:
    /// Number of rows
    int rows;
    /// Number of columns
    int columns;

public:
    /// The current board
    std::vector<std::vector<Piece*>> cannonBoard;
    /// The list of Soldier pieces, 0 represent Black Soldiers and 1 represents white
    std::vector< std::vector<Position> > positionsOfSoldiersOnBoard; //


    /// Constructor
    Board(int = 8, int = 8);
    /// Free memory
    void freeMemory();
    /// Temp function to print board
    void printBoard();
    /// returns the number of rows
    int getRows();
    /// returns the number of columns
    int getColumns();

    /// Returns number of White Townhalls remaining
    int numberOfWhiteTownhalls();

    /// Returns number of Black Townhalls remaining
    int numberOfBlackTownhalls();

    int numberOfCannonsOnBoard(std::vector< std::vector<Position> > &, int);
};
#endif
