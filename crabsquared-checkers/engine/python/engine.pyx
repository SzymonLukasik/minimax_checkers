# distutils: language = c++

from engine cimport valid_moves as valid_moves_c

chtoenum = {
    'b': 0,
    'w': 1,
    'B': 2,
    'W': 3,
    '.': 4,
}

def valid_moves(char_board, color):
    cdef board_t board
    board = board_t(BOARD_HEIGHT, vector[piece_t](BOARD_WIDTH))
    for i, row in enumerate(char_board):
        for j, sq in enumerate(row):
            board[i][j] = chtoenum[sq]
    
    return valid_moves_c(board, color)