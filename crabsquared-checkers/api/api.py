from crypt import methods
import time
from time import sleep
from flask import Flask, request

app = Flask(__name__)


@app.route('/available_moves', methods=['POST'])
def get_avaliable_moves():
    assert (request.json['type'] == 'board')
    board = request.json['state']
    return {
        'type': 'available_moves', 
        'available_moves': {
            'A1': [['A1', 'B2']]
        }
    }

@app.route('/bot_move', methods=['POST'])
def get_bot_move():
    assert (request.json['type'] == 'board')
    board = request.json['state']
    return {
        'type': 'bot_move',
        'move': ['A1', 'A2']
    }