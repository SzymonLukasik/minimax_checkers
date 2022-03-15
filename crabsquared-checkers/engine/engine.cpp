#include "engine.h"
#include <cmath>
#include <vector>


inline int reindex2to1(pos_t pos_h, pos_t pos_w){
    return BOARD_WIDTH*pos_h + pos_w;
}

inline bool are_oposing_colors(piece_color_t color1, piece_color_t color2){
    return  color1 != N && color2 != N
            && color1 != O && color2 != O
            && color1 != color2;
}

/*
    Returns true iff pos is in board bounds.
*/
inline bool in_board(pos_t pos_h, pos_t pos_w){
    return pos_h >= 0 && pos_h < BOARD_HEIGHT
            && pos_w >= 0 && pos_w < BOARD_WIDTH;
}

/*
    Converts pos to sqare name.
*/
inline std::string square_name(pos_t pos_h, pos_t pos_w){
    return {char(pos_w + char('A')), char(pos_h + char('1'))};
}

std::list<pos_t> get_dirs_h(piece_t piece){
    std::list<pos_t> dirs_h;
    if(piece == BK || piece == WK){
        dirs_h = {-1,1};
    } else if(piece == BP){
        dirs_h = {-1};
    } else {
        dirs_h = {1};
    }
    return dirs_h;
}

/*
    Returns color of a pice at given pos.
*/
piece_color_t piece_color(board_t const& board, pos_t pos_h, pos_t pos_w){
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
                                pos_t pos_h, pos_t pos_w,
                                piece_color_t color,
                                bool& capture_possible);
valid_moves_t filter_non_capture_moves(valid_moves_t const& moves);
valid_moves_t valid_moves(board_t const& board, piece_color_t color){
    valid_moves_t ret;
    bool capture_possible = false;
    for(pos_t pos_h = 0; pos_h < BOARD_HEIGHT; pos_h++){
        for(pos_t pos_w = pos_h%2; pos_w < BOARD_WIDTH; pos_w+=2){
            bool capture_possible_tmp = false;
            move_list_t square_move_list = square_valid_moves(board,
                                                        pos_h, pos_w,
                                                        color,
                                                        capture_possible_tmp);
            if(!square_move_list.empty())
                ret[square_name(pos_h, pos_w)] = square_move_list;

            capture_possible |= capture_possible_tmp;
        }
    }
    if(capture_possible)
        ret = filter_non_capture_moves(ret);

    return ret;
}

/*
    Returns a list of legal moves for given board, player color and square.
    Sets flag 'capture_possible' to 'true' iff a move which is a capture
    is possible at given square.
*/
move_list_t list_non_capture_moves(board_t const & board,
                                pos_t pos_h, pos_t pos_w);
move_list_t list_capture_moves(board_t const & board,
                                pos_t pos_h, pos_t pos_w,
                                bool& capture_possible);
move_list_t square_valid_moves(board_t const& board,
                                pos_t pos_h, pos_t pos_w,
                                piece_color_t color,
                                bool& capture_possible){
    move_list_t ret;
    if(color != piece_color(board, pos_h, pos_w))
        return ret;
    
    auto non_capture_moves = list_non_capture_moves(board, pos_h, pos_w);
    auto capture_moves = list_capture_moves(board, pos_h, pos_w, capture_possible);
    ret.insert(ret.end(), capture_moves.begin(), capture_moves.end());
    ret.insert(ret.end(), non_capture_moves.begin(), non_capture_moves.end());
    return ret;
}

/*
    Returns a list of legal non capture moves for given board, player color and square.
*/
move_list_t list_non_capture_moves(board_t const & board,
                                pos_t pos_h, pos_t pos_w){
    move_list_t ret;
    std::list<pos_t> dirs_h = get_dirs_h(board[pos_h][pos_w]);
    pos_t dirs_w[2] = {-1, 1};
    for(pos_t dir_h : dirs_h){
        for(pos_t dir_w : dirs_w){
            pos_t cur_h = pos_h+dir_h;
            pos_t cur_w = pos_w+dir_w;
            if(piece_color(board, cur_h, cur_w) == N)
                ret.push_back(
                    {square_name(pos_h, pos_w),
                    square_name(cur_h, cur_w)});
        }
    }
    return ret;
}

/*
    Returns a list of legal capture moves for given board, player color and square.
    Sets flag 'capture_possible' to 'true' iff a move which is a capture
    is possible at given square.
*/
move_list_t list_capture_moves_helper(board_t const & board,
                            pos_t pos_h, pos_t pos_w,
                            piece_color_t color, piece_t piece,
                            bool& capture_possible,
                            bool* captured,
                            pos_t ignore_pos_h, pos_t ignore_pos_w);
move_list_t filter_helper_artefact_moves(move_list_t const& move_list);
move_list_t list_capture_moves(board_t const & board,
                            pos_t pos_h, pos_t pos_w,
                            bool& capture_possible){
    bool captured[BOARD_HEIGHT * BOARD_WIDTH];
    piece_color_t color = piece_color(board, pos_h, pos_w);
    piece_t piece = board[pos_h][pos_w];
    move_list_t ret_tmp =
        list_capture_moves_helper(board, pos_h, pos_w, color, piece, capture_possible, captured, pos_h, pos_w);
    
    return filter_helper_artefact_moves(ret_tmp);
}

move_list_t list_capture_moves_helper(board_t const & board,
                            pos_t pos_h, pos_t pos_w,
                            piece_color_t color, piece_t piece,
                            bool& capture_possible,
                            bool* captured,
                            pos_t ignore_pos_h, pos_t ignore_pos_w){
    move_list_t ret;
    std::list<pos_t> dirs_h = get_dirs_h(piece);
    pos_t dirs_w[2] = {-1, 1};
    for(pos_t dir_h : dirs_h){
        for(pos_t dir_w : dirs_w){
            pos_t fst_h = pos_h+dir_h;
            pos_t fst_w = pos_w+dir_w;
            piece_color_t fst_neigh_color = piece_color(board, fst_h, fst_w);
            if(are_oposing_colors(color, fst_neigh_color)
            && !captured[reindex2to1(fst_h, fst_w)]){
                pos_t snd_h = fst_h + dir_h;
                pos_t snd_w = fst_w + dir_w;
                piece_color_t snd_neigh_color = piece_color(board, snd_h, snd_w);
                if(snd_neigh_color == N
                || (snd_h == ignore_pos_h && snd_w == ignore_pos_w)){
                    captured[reindex2to1(fst_h, fst_w)] = true;
                    move_list_t ret_tmp;
                    ret_tmp = list_capture_moves_helper(board, snd_h, snd_w, color, piece, capture_possible, captured, ignore_pos_h, ignore_pos_w);
                    capture_possible = true;
                    captured[reindex2to1(fst_h, fst_w)] = false;
                    
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

move_list_t filter_helper_artefact_moves(move_list_t const& move_list){
    move_list_t ret;
    for(auto move : move_list){
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
valid_moves_t filter_non_capture_moves(valid_moves_t const& moves){
    valid_moves_t ret;
    for(auto& square_moves : moves){
        move_list_t square_move_list = filter_square_non_capture_moves(square_moves.second);
        if(!square_move_list.empty())
            ret[square_moves.first] = square_move_list;
    }
    return ret;
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
    std::cout<<valid_moves(board2, W);
    
    return 0;
}