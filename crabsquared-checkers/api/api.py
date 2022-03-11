import time
from time import sleep
from flask import Flask

app = Flask(__name__)

@app.route('/time')
def get_test_value():
    return {'time': time.time()}