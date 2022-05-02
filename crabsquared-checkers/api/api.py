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

# Tests
import json

@app.route('/test')
def test():
    client = app.test_client()

    print('Test 1')
    response = client.get('/')
    json_data = json.loads(response.data)

    assert json_data['type'] == 'api_base'
    assert '/bot_move' in json_data['available_requests']
    print('Test 1 - OK\n')


    print('Test 2')
    response = client.post('/available_moves', json={
        'type': 'board',
        'state': [
            ['.','b','.','b','.','.','.'],
            ['.','.','.','.','.','.','.'],
            ['.','b','.','b','.','.','.'],
            ['.','.','W','.','.','.','.'],
            ['.','b','.','.','.','.','.'],
            ['.','.','.','.','.','.','.'],
            ['.','.','.','.','.','.','.'],
        ]
    })
    json_data = json.loads(response.data)
    moves = json_data['available_moves']['C4']
    assert ['C4', 'A2'] in moves
    assert ['C4', 'E2'] in moves
    assert ['C4', 'A6'] in moves
    print('Test 2 - OK\n')


    # Awaiting engine fix.
    # print('Test 3')
    # response = client.post('/available_moves', json={
    #     'type': 'board',
    #     'state': [
    #         ['.','b','.','b','.','.','.'],
    #         ['.','.','.','.','.','.','.'],
    #         ['.','b','.','b','.','.','.'],
    #         ['.','.','w','.','.','.','.'],
    #         ['.','.','.','.','.','.','.'],
    #         ['.','.','.','.','.','.','.'],
    #         ['.','.','.','.','.','.','.'],
    #     ]
    # })
    # json_data = json.loads(response.data)
    # moves = json_data['available_moves']['C4']
    # print(moves)
    # assert ['C4', 'A2'] in moves
    # assert ['C4', 'E2'] in moves
    # print(json_data)
    # print('Test 3 - OK')


    print('Test 4')
    response = client.post('/bot_move', json={
        'type': 'board',
        'state': [
            ['.','b','.','b','.','.','.'],
            ['.','.','.','.','.','.','.'],
            ['.','b','.','b','.','.','.'],
            ['.','.','w','.','.','.','.'],
            ['.','.','.','.','.','.','.'],
            ['.','.','.','.','.','.','.'],
            ['.','.','.','.','.','.','.'],
        ]
    })
    json_data = json.loads(response.data)
    assert json_data['type'] == 'bot_move'
    print('Test 4 - OK')

    return 'Test OK'