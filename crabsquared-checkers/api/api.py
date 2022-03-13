import time
from time import sleep
from flask import Flask, request

app = Flask(__name__)

@app.route('/test', methods=['POST'])
def get_test_variable():
    var = request.json['var']
    return {'var': var + 1}