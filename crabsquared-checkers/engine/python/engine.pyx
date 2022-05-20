# distutils: language = c++

from engine cimport valid_moves as valid_moves_c
from engine cimport get_board_after_move as get_board_after_move_c

chtoenum = {
    'b': 0,
    'w': 1,
    'B': 2,
    'W': 3,
    '.': 4,
}

enumtoch = {v: k for (k, v) in chtoenum.items()}

def char_to_engine_board(char_board):
    return [
        [chtoenum[sq] for sq in row]
        for row in char_board
    ]

def engine_to_char_board(engine_board):
    return [
        [enumtoch[sq] for sq in row]
        for row in engine_board
    ]

def pair_to_str(p):
    row, col = p
    row_char = chr(ord('1')+row)
    col_char = chr(ord('A')+col)
    return col_char + row_char

def str_to_pair(s):
    assert(len(s) == 2)
    col_char, row_char = s
    col, row = ord(col_char) - ord('A'), ord(row_char) - ord('1')
    return [row, col]

def engine_to_char_moves(engine_moves):
    return {
        pair_to_str(sq) : [
            [pair_to_str(mv_sq) for mv_sq in move]
            for move in moves
        ]
        for sq, moves in engine_moves.items()
    }

def char_to_engine_move(char_move):
    return [str_to_pair(mv_sq) for mv_sq in char_move]

def valid_moves(char_board, color):
    board = char_to_engine_board(char_board)
    engine_moves = valid_moves_c(board, color)
    char_moves = engine_to_char_moves(engine_moves)
    return char_moves

def get_board_after_move(char_board, char_move):
    board = char_to_engine_board(char_board)
    move = char_to_engine_move(char_move)
    engine_board = get_board_after_move_c(board, move)
    return engine_to_char_board(engine_board)