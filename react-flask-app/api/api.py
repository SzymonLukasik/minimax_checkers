import time
from time import sleep
from flask import Flask

app = Flask(__name__)

@app.route('/time')
def get_current_time():
    return {'time': time.time()}

@app.route('/move')
def get_next_move():
    sleep(4) # tutaj może być uruchamiany model
    return {'move': 'A5 B4'}