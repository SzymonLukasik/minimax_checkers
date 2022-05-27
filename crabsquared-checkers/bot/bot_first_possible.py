import os
print (os.getcwd())

from engine.python import engine
from .bot_abstract import bot_abstract

class bot_first_possible(bot_abstract):
    def get_name(self):
        return 'bot_first_possible'

    def get_move(self, board, parameters = {}):
        valid_moves = engine.valid_moves(board, 1)
        move_start_pos = next(iter(valid_moves))
        move = valid_moves[move_start_pos][0]
        return move
