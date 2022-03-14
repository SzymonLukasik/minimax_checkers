#include "engine.h"
#include <cmath>
#include <vector>

/*
    Returns true iff pos is in board bounds.
*/
bool in_board(int pos_h, int pos_w){
    return pos_h >= 0 && pos_h < BOARD_HEIGHT
            && pos_w >= 0 && pos_w < BOARD_WIDTH;
}

/*
    Converts pos to sqare name.
*/
std::string square_name(int pos_h, int pos_w){
    char row = char(pos_h) + '1';
    char col = char(pos_w) + 'A';
    return {col, row};
}

/*
    Returns color of a pice at given pos.
*/
piece_color_t piece_color(board_t const& board, int pos_h, int pos_w){
    if(!in_board(pos_h, pos_w))
        return O;
    piece_t piece = board[pos_h][pos_w];
    if(piece == BP || piece == BK)
        return B;
    if(piece == WP || piece == WK)
        return W;
    return N;
}

/*
    Return a map of valid moves for given board and player color.
*/
move_list_t square_valid_moves(board_t const& board,
                                int pos_h, int pos_w,
                                piece_color_t color,
                                bool& capture_possible);
void filter_non_capture_moves(valid_moves_t& moves);
valid_moves_t valid_moves(board_t const& board, piece_color_t color){
    valid_moves_t ret;
    bool capture_ocurred = false;
    for(int pos_h = 0; pos_h < BOARD_HEIGHT; pos_h++){
        for(int pos_w = 0; pos_w < BOARD_WIDTH; pos_w++){
            bool capture_ocurred_tmp;
            ret[square_name(pos_h, pos_w)] =
                square_valid_moves(board,
                                    pos_h, pos_w,
                                    color,
                                    capture_ocurred_tmp);
            capture_ocurred |= capture_ocurred_tmp;
        }
    }
    if(capture_ocurred){
        filter_non_capture_moves(ret);
    }
    return ret;
}

/*
    Returns a list of legal moves for given board, player color and square.
    Sets flag 'capture_possible' to 'true' iff a move which is a capture
    is possible at given square.
*/
move_list_t list_non_capture_moves(board_t const & board,
                                int pos_h, int pos_w);
move_list_t list_capture_moves(board_t const & board,
                                int pos_h, int pos_w,
                                piece_color_t color,
                                bool& capture_possible);
move_list_t square_valid_moves(board_t const& board,
                                int pos_h, int pos_w,
                                piece_color_t color,
                                bool& capture_possible){
    move_list_t ret;
    if(color != piece_color(board, pos_h, pos_w))
        return ret;
    
    auto non_capture_moves = list_non_capture_moves(board, pos_h, pos_w);
    auto capture_moves = list_capture_moves(board, pos_h, pos_w, color, capture_possible);
    ret.insert(ret.end(), capture_moves.begin(), capture_moves.end());
    ret.insert(ret.end(), non_capture_moves.begin(), non_capture_moves.end());
    return ret;
}

/*
    Returns a list of legal non capture moves for given board, player color and square.
*/
move_list_t list_non_capture_moves(board_t const & board,
                                int pos_h, int pos_w){
    move_list_t ret;
    std::list<int> dirs_h;
    piece_t piece = board[pos_h][pos_w];
    if(piece == BK || piece == WK){
        dirs_h = {-1,1};
    } else if(piece == BP){
        dirs_h = {-1};
    } else {
        dirs_h = {1};
    }
    int dirs_w[2] = {-1, 1};
    for(int dir_h : dirs_h){
        for(int dir_w : dirs_w){
            int cur_h = pos_h+dir_h;
            int cur_w = pos_w+dir_w;
            if(piece_color(board, cur_h, cur_w) == N)
                ret.push_back(
                    {square_name(pos_h, pos_w),
                    square_name(cur_h, cur_w)});
        }
    }
    return ret;
}

move_list_t list_capture_moves_helper(board_t const & board,
                            int pos_h, int pos_w,
                            piece_color_t color, piece_t piece,
                            bool& capture_possible,
                            std::vector<std::vector<bool>>& captured,
                            int ignore_pos_h, int ignore_pos_w){
    move_list_t ret;
    std::list<int> dirs_h;
    if(piece == BK || piece == WK){
        dirs_h = {-1,1};
    } else if(piece == BP){
        dirs_h = {-1};
    } else {
        dirs_h = {1};
    }
    int dirs_w[2] = {-1, 1};
    for(int dir_h : dirs_h){
        for(int dir_w : dirs_w){
            int fst_h = pos_h+dir_h;
            int fst_w = pos_w+dir_w;
            piece_color_t fst_neigh_color = piece_color(board, fst_h, fst_w);
            if(fst_neigh_color != N
            && fst_neigh_color != O
            && fst_neigh_color != color
            && !captured[fst_h][fst_w]){
                int snd_h = fst_h + dir_h;
                int snd_w = fst_w + dir_w;
                piece_color_t snd_neigh_color = piece_color(board, snd_h, snd_w);
                if(snd_neigh_color == N
                || (snd_h == ignore_pos_h && snd_w == ignore_pos_w)){
                    captured[fst_h][fst_w] = true;
                    move_list_t ret_tmp;
                    ret_tmp = list_capture_moves_helper(board, snd_h, snd_w, color, piece, capture_possible, captured, ignore_pos_h, ignore_pos_w);
                    capture_possible = true;
                    captured[fst_h][fst_w] = false;
                    
                    for(auto& move : ret_tmp){
                        move.insert(move.begin(), {square_name(pos_h, pos_w)});
                    }
                    ret.insert(ret.end(), ret_tmp.begin(), ret_tmp.end());
                }
            }
        }
    }
    if(ret.empty())
        return {{square_name(pos_h, pos_w)}};
    return ret;
}

/*
    Returns a list of legal capture moves for given board, player color and square.
    Sets flag 'capture_possible' to 'true' iff a move which is a capture
    is possible at given square.
*/
move_list_t list_capture_moves(board_t const & board,
                            int pos_h, int pos_w,
                            piece_color_t color,
                            bool& capture_possible){
    std::vector<std::vector<bool>> captured(BOARD_HEIGHT, std::vector<bool>(BOARD_WIDTH, false));
    move_list_t ret_tmp =
        list_capture_moves_helper(board, pos_h, pos_w, color, board[pos_h][pos_w], capture_possible, captured, pos_h, pos_w);
    move_list_t ret;
    for(auto move : ret_tmp){
        if(move.size() > 1)
            ret.push_back(move);
    }
    return ret;
}

/*
    Returns true iff a move is a capture.
*/
bool is_capture_move(move_t const& move){
    square_t sq0 = *(move.begin());
    square_t sq1 = *(++move.begin());
    return abs(sq0[0] - sq1[0]) > 1;
}

move_list_t filter_square_non_capture_moves(move_list_t const& moves){
    move_list_t ret;
    for(auto move : moves){
        if(is_capture_move(move))
            ret.push_back(move);
    }
    return ret;
}

/*
    Filters moves so that only capture moves remain.
*/
void filter_non_capture_moves(valid_moves_t& moves){
    for(auto& square_moves : moves){
        square_moves.second = filter_square_non_capture_moves(square_moves.second);
    }
}






/// tests. TODO


#include <iostream>
std::ostream& operator <<(std::ostream& os, move_t mv){
    for(auto sq : mv){
        os<<sq<<" ";
    }
    return os;
}
std::ostream& operator <<(std::ostream& os, move_list_t ml){
    for(auto mv : ml){
        os<<"{"<<mv<<"}";
    }
    return os;
}
std::ostream& operator <<(std::ostream& os, std::pair<square_t, move_list_t> p){
    os<<p.first<<": "<<p.second;
    return os;
}
std::ostream& operator <<(std::ostream& os, valid_moves_t vm){
    for(auto m : vm){
        std::cout<<m<<std::endl;
    }
    return os;
}

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


int main(){
    std::cout<<valid_moves(board1, W);
    
    return 0;
}