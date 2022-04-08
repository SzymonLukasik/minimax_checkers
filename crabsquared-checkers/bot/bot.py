from ..engine.python import engine

def get_move(board):
    valid_moves = engine.valid_moves(board, 1)
    move_start_pos = next(iter(valid_moves))
    move = valid_moves[move_start_pos][0]
    return move