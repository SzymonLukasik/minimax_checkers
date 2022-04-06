from flask import request
from ..app import app
from ..bot.bot import get_move
from ..engine.python import engine

@app.route('/')
def api_base():
    return {
        'type': 'api_base',
        'available_requests': ['/', '/available_moves', '/bot_move']
    }

@app.route('/available_moves', methods=['POST'])
def get_avaliable_moves():
    board = request.json['state']
    moves = engine.valid_moves(board, 1)
    return {
        'type': 'available_moves', 
        'available_moves': moves
    }

@app.route('/bot_move', methods=['POST'])
def get_bot_move():
    board = request.json['state']
    move = get_move(board)
    return {
        'type': 'bot_move',
        'move': move
    }