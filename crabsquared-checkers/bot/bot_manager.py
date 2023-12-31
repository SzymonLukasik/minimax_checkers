from .bot_first_possible import bot_first_possible
from .bot_random import bot_random
from .bot_minimax import bot_minimax, bot_minimax_hard

class bot_manager:
    bots = {}

    def add_bot(bot):
        bot_manager.bots[bot.get_name()] = bot

    def get_move(name, board, parameters = {}):
        return bot_manager.bots[name].get_move(board, parameters)

bot_manager.add_bot(bot_first_possible())
bot_manager.add_bot(bot_random())
bot_manager.add_bot(bot_minimax())
bot_manager.add_bot(bot_minimax_hard())
