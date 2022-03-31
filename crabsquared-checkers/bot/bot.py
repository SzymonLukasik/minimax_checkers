from idna import valid_contexto
from ..engine.python import engine

def get_move(board):
    print(board)
    
    valid_moves = engine.valid_moves(board, 1)
    print(valid_moves)
    
    move_start_pos = next(iter(valid_moves))
    print(move_start_pos)

    move = valid_moves[move_start_pos][0]
    print(move)

    return move