#include "engine.h"
#include <cmath>
#include <vector>
#include <bitset>
#include <algorithm>

/// TESTS

#include <iostream>
/*
    Converts pos to sqare name.
    Eg: (1,2) -> "C2"
        (3,5) -> "F4"
*/
inline std::string sqtostr(square_t sq)
{
    return {char(sq.second + char('A')), char(sq.first + char('1'))};
}
pos_t board_width(board_t const& board);
pos_t board_height(board_t const& board);

board_t board1 = {
    {WP, NP, WP, NP, WP, NP, WP, NP},
    {NP, WP, NP, WP, NP, WP, NP, WP},
    {WP, NP, WP, NP, WP, NP, WP, NP},
    {NP, NP, NP, NP, NP, NP, NP, NP},
    {NP, NP, WP, NP, NP, NP, NP, NP},
    {NP, BP, NP, BP, NP, BP, NP, BP},
    {BP, NP, BP, NP, BP, NP, BP, NP},
    {NP, BP, NP, BP, NP, BP, NP, BP},
};

board_t board2 = {
    {NP, NP, NP, NP, NP, NP, NP, NP},
    {NP, BP, NP, BP, NP, NP, NP, NP},
    {NP, NP, NP, NP, NP, NP, NP, NP},
    {NP, BP, NP, BP, NP, NP, NP, NP},
    {NP, NP, WK, NP, NP, NP, NP, NP},
    {NP, NP, NP, NP, NP, NP, NP, NP},
    {NP, NP, NP, NP, NP, NP, NP, NP},
    {NP, NP, NP, NP, NP, NP, NP, NP},
};

std::ostream &operator<<(std::ostream &os, square_t sq)
{
    os << sqtostr(sq);
    return os;
}
std::ostream &operator<<(std::ostream &os, move_t mv)
{
    for (auto sq : mv)
    {
        os << sq << " ";
    }
    return os;
}
std::ostream &operator<<(std::ostream &os, square_moves_t ml)
{
    for (auto mv : ml)
    {
        os << "{" << mv << "}";
    }
    return os;
}
std::ostream &operator<<(std::ostream &os, std::pair<square_t, square_moves_t> p)
{
    os << p.first << ": " << p.second;
    return os;
}
std::ostream &operator<<(std::ostream &os, board_moves_t vm)
{
    for (auto m : vm)
    {
        std::cout << m << std::endl;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, board_t board)
{
    for (pos_t i = 0; i < board_height(board); i++)
    {
        for (pos_t j = 0; j < board_width(board); j++)
        {
            os << board[i][j];
        }
        os << "\n";
    }
    return os;
}

/// IMPLEMENTATION

/*
    Vector indicating in which direction to push a piece.
*/
using dir_t = square_t;

square_t operator+(square_t sq, dir_t dir)
{
    return {sq.first + dir.first, sq.second + dir.second};
}

bool operator==(square_t sq1, square_t sq2)
{
    return sq1.first == sq2.first && sq1.second == sq2.second;
}

inline pos_t board_height(board_t const& board){
    return board.size();
}

inline pos_t board_width(board_t const& board){
    return board[0].size();
}

inline pos_t board_n_squares(board_t const& board){
    return board_height(board) * board_width(board);
}

/*
    Convert square_t to int used in indexing std::bitset<N_SQUARES>.
*/
inline int sqto1d(board_t const& board, square_t sq)
{
    return board_width(board) * sq.first + sq.second;
}

/*
    Oposing colors are white and black.
*/
inline bool are_oposing_colors(piece_color_t color1, piece_color_t color2)
{
    return color1 != N && color2 != N && color1 != color2;
}

/*
    Returns true iff 'sq' is in [0, board_height(board)) x [0, board_width(board)).
*/
inline bool in_board(board_t const& board, square_t sq)
{
    return sq.first >= 0 && sq.first < board_height(board) && sq.second >= 0 && sq.second < board_width(board);
}

/*
    Returns list of directions in which given piece can be pushed.
    Ignores board bounds.
*/
std::list<dir_t> piece_dirs(piece_t piece)
{
    std::list<pos_t> dirs_h;
    if (piece == BK || piece == WK)
    {
        dirs_h = {-1, 1};
    }
    else if (piece == BP)
    {
        dirs_h = {-1};
    }
    else
    {
        dirs_h = {1};
    }
    std::list<pos_t> dirs_w = {-1, 1};
    std::list<dir_t> ret;
    for (auto dir_h : dirs_h)
    {
        for (auto dir_w : dirs_w)
        {
            ret.push_back({dir_h, dir_w});
        }
    }
    return ret;
}

/*
    Returns list of all possible squares for given board.
*/
std::list<square_t> board_squares(board_t const& board){
    std::list<square_t> ret;
    for (pos_t pos_h = 0; pos_h < board_height(board); pos_h++)
    {
        for (pos_t pos_w = 0; pos_w < board_width(board); pos_w++)
        {
            ret.push_back({pos_h, pos_w});
        }
    }
    return ret;
}

/*
    Returns color of a given piece.
*/
piece_color_t piece_color(piece_t piece)
{
    if (piece == BP || piece == BK)
        return B;
    if (piece == WP || piece == WK)
        return W;
    return N;
}

/*
    Safe way to query 'board' at square 'sq'.
    Returns 'O' if out of bounds query.
*/
piece_t get_piece(board_t const &board, square_t sq)
{
    if (!in_board(board, sq))
        return O;
    return board[sq.first][sq.second];
}

square_moves_t square_valid_moves(board_t const &board,
                                  square_t sq,
                                  piece_color_t color,
                                  bool &capture_possible);
void remove_non_capture_moves(board_moves_t &moves);
board_moves_t valid_moves(board_t const &board, piece_color_t color)
{
    board_moves_t ret;
    bool capture_possible = false;
    for(square_t sq : board_squares(board)){
        bool capture_possible_tmp = false;
        square_moves_t square_moves = square_valid_moves(board,
                                                        sq,
                                                        color,
                                                        capture_possible_tmp);
        if (!square_moves.empty())
            ret[sq] = square_moves;

        capture_possible |= capture_possible_tmp;
    }
    
    if (capture_possible)
        remove_non_capture_moves(ret);

    return ret;
}

square_moves_t square_non_capture_moves(board_t const &board,
                                        square_t sq);
square_moves_t square_capture_moves(board_t const &board,
                                    square_t sq,
                                    bool &capture_possible);
/*
    Returns a list of legal moves for given board, player color and square.
    Sets flag 'capture_possible' to 'true' iff a move which is a capture
    is possible at given square.
*/
square_moves_t square_valid_moves(board_t const &board,
                                  square_t sq,
                                  piece_color_t color,
                                  bool &capture_possible)
{
    if (color != piece_color(get_piece(board, sq)))
        return {};

    square_moves_t ret = square_capture_moves(board, sq, capture_possible);
    if (!capture_possible)
        ret = square_non_capture_moves(board, sq);
    return ret;
}

/*
    Returns a list of legal non capture moves for given board, player color and square.
*/
square_moves_t square_non_capture_moves(board_t const &board,
                                        square_t sq)
{
    square_moves_t ret;
    for (auto dir : piece_dirs(get_piece(board, sq)))
    {
        square_t cur_sq = sq + dir;
        if (get_piece(board, cur_sq) == NP)
            ret.push_back({sq, cur_sq});
    }

    return ret;
}

using visited_t = std::vector<std::vector<bool>>;
square_moves_t square_capture_moves_helper(board_t const &board,
                                           square_t sq,
                                           bool &capture_possible,
                                           visited_t &captured,
                                           square_t start_sq);
/*
    Returns a list of legal capture moves for given board, player color and square.
    Sets flag 'capture_possible' to 'true' iff a move which is a capture
    is possible at given square.
*/
square_moves_t square_capture_moves(board_t const &board,
                                    square_t sq,
                                    bool &capture_possible)
{
    auto captured = visited_t(
        board_height(board),
        std::vector<bool>(
            board_width(board),
            false));
    
    square_moves_t ret_tmp =
        square_capture_moves_helper(board, sq, capture_possible, captured, sq);
    // Erase artefact moves created by helper function.
    ret_tmp.erase(
        std::remove_if(ret_tmp.begin(), ret_tmp.end(), [](move_t mv)
                       { return mv.size() <= 1; }),
        ret_tmp.end());
    return ret_tmp;
}

/*
    sq          - currently considered square
    captured    - entry set to true iff a piece at given square has bee captured
    start_sq    - square at which we start the capturing sequence
*/
square_moves_t square_capture_moves_helper(board_t const &board,
                                           square_t sq,
                                           bool &capture_possible,
                                           visited_t &captured,
                                           square_t start_sq)
{
    square_moves_t ret;
    // The piece which we are moving.
    // 'board' is immutable therefore this piece sits on 'start_sq'.
    piece_t piece = get_piece(board, start_sq);
    piece_color_t color = piece_color(piece);
    for (auto dir : piece_dirs(piece))
    {
        square_t fst_sq = sq + dir;
        piece_color_t fst_color = piece_color(get_piece(board, fst_sq));
        // If a piece is of oposing color and hasn't been captured yet
        // we can consider capturing it.
        if (are_oposing_colors(color, fst_color)
            && !captured[fst_sq.first][fst_sq.second])
        {
            square_t snd_sq = fst_sq + dir;
            piece_t snd_piece = get_piece(board, snd_sq);
            // If the square after 'fst_sq' is free then we can capture
            // the piece from 'fst_sq'.
            if (snd_piece == NP || snd_sq == start_sq)
            {
                captured[fst_sq.first][fst_sq.second] = true;
                // Get capturing sequence starting from 'snd_sq'.
                square_moves_t ret_tmp = square_capture_moves_helper(board, snd_sq, capture_possible, captured, start_sq);
                capture_possible = true;
                captured[fst_sq.first][fst_sq.second] = false;

                // Prepend 'sq' to obtained capturing sequence.
                for (auto &move : ret_tmp)
                    move.push_front(sq);

                // Append updated moves to 'ret'.
                ret.insert(ret.end(), ret_tmp.begin(), ret_tmp.end());
            }
        }
    }
    // If no capture is possible from 'sq' then return
    // list {{sq}} as a base case for recursion.
    if (ret.empty())
        return {{sq}};

    return ret;
}

/*
    Returns true iff a move is a capture.
    Assumes that given move is of valid format.
*/
bool is_capture_move(move_t const &move)
{
    square_t sq0 = *(move.begin());
    square_t sq1 = *(++move.begin());
    return abs(sq0.first - sq1.first) > 1;
}

/*
    Modify 'board_moves' so that only capture moves remain.
    Clear entries containing empty move lists.
*/
void remove_non_capture_moves(board_moves_t &board_moves)
{
    for (auto it = board_moves.begin(); it != board_moves.end();)
    {
        square_moves_t moves = it->second;
        moves.erase(
            std::remove_if(moves.begin(), moves.end(), [](move_t mv)
                           { return !is_capture_move(mv); }),
            moves.end());
        if (moves.empty())
        {
            it = board_moves.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

/// tests. TODO

int main()
{
    std::cout << valid_moves(board2, W);

    return 0;
}