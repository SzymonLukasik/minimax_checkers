from libcpp.map cimport map
from libcpp.list cimport list
from libcpp.utility cimport pair
from libcpp.vector cimport vector

cdef extern from "../engine.cpp":
    pass

cdef extern from "../engine.h":
    enum piece_t:
        BP,
        WP,
        BK,
        WK,
        NP,
        O
    enum piece_color_t:
        B,
        W,
        N
    int BOARD_HEIGHT
    int BOARD_WIDTH

    ctypedef pair[int, int] square_t 
    ctypedef list[square_t] move_t 
    ctypedef list[move_t] square_moves_t
    ctypedef vector[vector[piece_t]] board_t

    map[square_t, square_moves_t] valid_moves(board_t& board, piece_color_t color)
