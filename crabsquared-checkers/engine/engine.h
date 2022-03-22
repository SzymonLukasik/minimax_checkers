#ifndef ENGINE_H
#define ENGINE_H

#include <list>
#include <map>
#include <vector>

/*
    BP - black pawn
    WP - white pawn
    BK - black king
    WK - white king
    NP - no piece
    O  - out of bounds
*/
enum piece_t
{
    BP,
    WP,
    BK,
    WK,
    NP,
    O
};
/*
    B - black
    W - white
    N - none
*/
enum piece_color_t
{
    B,
    W,
    N,
};

const int BOARD_WIDTH = 8;
const int BOARD_HEIGHT = 8;
const int N_SQUARES = BOARD_WIDTH * BOARD_HEIGHT;

/*
    Number describing single coordinate on a board.
*/
using pos_t = int;

using square_t = std::pair<pos_t, pos_t>;

using board_t = std::vector<std::vector<piece_t>>;

/*
    A list of squares to visit in order to make a valid move.

    Eg: move_t mv1 = ["A3", "B4"]
        move_t mv2 = ["A3", "C5", "E7"]
*/
using move_t = std::list<square_t>;

/*
    A list of possible moves from a square.
    Eg: move_t mv1  = ["A3", "C5", "A7"]
        move_t mv2  = ["A3", "C5", "E7"]
        square_moves_t sq_mv = [mv1, mv2];
*/
using square_moves_t = std::list<move_t>;

/*
    A map of all valid moves in a possition.
    If a move which is a capture is possible,
    should exclude all non-capture moves.
*/
using board_moves_t = std::map<square_t, square_moves_t>;

/*
    Return a map of valid moves for given board and player color.
*/
board_moves_t valid_moves(board_t const &board, piece_color_t color);

#endif