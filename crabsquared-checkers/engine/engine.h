#include <list>
#include <map>

/*
    Eg: square_t sq = "A4"
*/
using square_t = std::string;

/*
    BP - black pawn
    WP - white pawn
    BK - black king
    WK - white king
    NP - no piece
*/
enum piece_t {BP, WP, BK, WK, NP};
/*
    B - black
    W - white
    N - none
    O - out of bounds
*/
enum piece_color_t {B, W, N, O};

const int BOARD_WIDTH = 8;
const int BOARD_HEIGHT = 8;

using board_t = piece_t[BOARD_HEIGHT][BOARD_WIDTH];

/*
    A list of squares to visit in order to make a valid move,
    .
    Eg: move_t mv1 = ["A3", "B4"]
        move_t mv2 = ["A3", "C5", "E7"]
*/
using move_t = std::list<square_t>;

/*
    A list of possible moves from a square.
    Eg: move_t mv1  = ["A3", "C5", "A7"]
        move_t mv2  = ["A3", "C5", "E7"]
        move_list_t = [mv1, mv2];
*/
using move_list_t = std::list<move_t>;

/*
    A map of all valid moves in a possition.
    If a move which is a capture is possible,
    should exclude all non-capture moves.
*/
using valid_moves_t = std::map<square_t, move_list_t>;

valid_moves_t valid_moves(board_t const& board, piece_color_t color);