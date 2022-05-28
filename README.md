# CrabSquared

### ML-Powered Checkers in progress...

### How to run app? 

1. Make sure, you have installed `Node.js`, `npm`, `npx`, `yarn`, `python`.
2. Also install `pip install flask python-dotenv Cython` to use api.
3. Go to `crabsquared-checkers` and run `npm install` to install needed dependencies.
4. Run `yarn compile`to compile engine.
5. Start an app by going to `crabsquared-checkers` and running `npm start`. 

### How to run from docker?
cd crabsquared-checkers
sudo docker build -t test . && sudo docker run -it -p 8000:8000 test

spushuj do heroku brancha deploy:
git push heroku deploy:master


### API Endpoints

`5000/available_moves` - returns available moves
`5000/bot_move` - returns one bot move


### Bots

Each bot is expected to provide get_move(board) function that takes board and returns bot's move. Board and move are represented the same way they are represented in jsons.
