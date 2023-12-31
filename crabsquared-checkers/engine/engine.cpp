#include <vector>
#include <bitset>
#include <algorithm>
#include <iostream>
#include <optional>

#include "engine.h"

pos_t board_width(board_t const& board);
pos_t board_height(board_t const& board);

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
    Opposing colors are white and black.
*/
inline bool are_opposing_colors(std::optional<piece_color_t> color1, std::optional<piece_color_t> color2)
{
    return color1.has_value() && color2.has_value() && color1 != color2;
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
std::list<dir_t> piece_dirs(std::optional<piece_t> piece)
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
std::optional<piece_color_t> piece_color(std::optional<piece_t> piece)
{
    if (piece == BP || piece == BK)
        return B;
    if (piece == WP || piece == WK)
        return W;
    return std::nullopt;
}

/*
    Safe way to query 'board' at square 'sq'.
    Returns 'std::nullopt' if out of bounds query.
*/
std::optional<piece_t> get_piece(board_t const &board, square_t sq)
{
    if (!in_board(board, sq))
        return std::nullopt;
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
    std::optional<piece_t> piece = get_piece(board, start_sq);
    std::optional<piece_color_t> color = piece_color(piece);
    for (auto dir : piece_dirs(piece))
    {
        square_t fst_sq = sq + dir;
        std::optional<piece_color_t> fst_color = piece_color(get_piece(board, fst_sq));
        // If a piece is of opposing color and hasn't been captured yet,
        // we can consider capturing it.
        if (are_opposing_colors(color, fst_color)
            && !captured[fst_sq.first][fst_sq.second])
        {
            square_t snd_sq = fst_sq + dir;
            std::optional<piece_t> snd_piece = get_piece(board, snd_sq);
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

/*
    Returns a vector of captured pieces.
*/
std::vector<square_t> get_captured_pieces(move_t move)
{
    if (!is_capture_move(move))
        return {};
    
    static auto get_middle_pos = [] (pos_t a, pos_t b) -> pos_t { return (a + b) / 2; };
    std::vector<square_t> ret;
    for (auto curr = move.begin(), next = std::next(move.begin());
         next != move.end();
         curr++, next++)
    {
        square_t captured = {
            get_middle_pos(curr->first, next->first), 
            get_middle_pos(curr->second, next->second)
        };
        ret.push_back(captured);
    }

    return ret;
}

void make_move(board_t &board, const move_t &move)
{
    std::vector<square_t> positions_to_clear = get_captured_pieces(move);
    positions_to_clear.push_back(*move.begin());

    square_t start_square = *move.begin();
    square_t end_square = *(std::prev(move.end()));
    piece_t moved_piece = board[start_square.first][start_square.second];
    
    for (square_t sq : positions_to_clear)
    {
        board[sq.first][sq.second] = piece_t::NP;            
    }
    board[end_square.first][end_square.second] = moved_piece;
}

board_t get_board_after_move(const board_t &board, const move_t &move)
{
    board_t ret = board;
    make_move(ret, move);
    return ret;
}