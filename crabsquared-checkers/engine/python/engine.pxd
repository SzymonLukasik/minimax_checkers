from libcpp.map cimport map
from libcpp.list cimport list
from libcpp.utility cimport pair
from libcpp.vector cimport vector

cdef extern from "../engine.cpp":
    pass

cdef extern from "../engine.h":
    enum piece_t:
        pass
    enum piece_color_t:
        pass

    ctypedef pair[int, int] square_t 
    ctypedef list[square_t] move_t 
    ctypedef list[move_t] square_moves_t
    ctypedef vector[vector[piece_t]] board_t
    ctypedef map[square_t, square_moves_t] board_moves_t
    
    board_moves_t valid_moves(board_t& board, piece_color_t color)
