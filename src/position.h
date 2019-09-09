#ifndef POSITION_H
#define POSITION_H
/// Position of a piece on the board
struct Position
{
    int x;
    int y;
};
/// Colour of a piece
enum class Colour: std::int8_t {black = 0, white = 1};
/// Type of piece
enum class PieceType: std::int8_t {soldier = 0, cannon = 1, townhall = 2};
#endif
