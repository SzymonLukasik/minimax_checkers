from flask import Flask, request
from ..bot.bot import get_move

app = Flask(__name__)

@app.route('/')
def api_base():
    return {
        'type': 'api_base',
        'available_requests': ['/', '/available_moves', '/bot_move']
    }

@app.route('/available_moves', methods=['POST'])
def get_avaliable_moves():
    board = request.json['state']
    return {
        'type': 'available_moves', 
        'available_moves': {
            'A1': [['A1', 'B2']]
        }
    }

@app.route('/bot_move', methods=['POST'])
def get_bot_move():
    board = request.json['state']
    get_move(board)
    return {
        'type': 'bot_move',
        'move': ['A1', 'A2']
    }