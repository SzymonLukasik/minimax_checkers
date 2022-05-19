from ..engine.python import engine
from .bot_abstract import bot_abstract
import random

class bot_random(bot_abstract):
    def get_name(self):
        return 'bot_random'

    def get_move(self, board, parameters = {}):
        valid_moves = engine.valid_moves(board, 1)
        move = random.choice(random.choice(list(valid_moves.values())))
        return move
