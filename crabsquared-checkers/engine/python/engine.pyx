# distutils: language = c++

from engine cimport valid_moves as valid_moves_c

chtoenum = {
    'b': 0,
    'w': 1,
    'B': 2,
    'W': 3,
    '.': 4,
}

def char_to_engine_board(char_board):
    return [
        [chtoenum[sq] for sq in row]
        for row in char_board
    ]

def pair_to_str(p):
    row, col = p
    row_char = chr(ord('1')+row)
    col_char = chr(ord('A')+col)
    return col_char + row_char

def engine_to_char_moves(engine_moves):
    return {
        pair_to_str(sq) : [
            [pair_to_str(mv_sq) for mv_sq in move]
            for move in moves
        ]
            for sq, moves in engine_moves.items()
    }

def valid_moves(char_board, color):
    board = char_to_engine_board(char_board)
    engine_moves = valid_moves_c(board, color)
    char_moves = engine_to_char_moves(engine_moves)
    return char_moves