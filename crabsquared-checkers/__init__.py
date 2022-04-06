from flask import Flask
app = Flask(__name__)

from .api.api import *