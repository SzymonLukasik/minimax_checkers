import { Position } from "./Position";

/**
 * Class enabling control over a move of a single piece. 
 * 
 * Definitions:
 *  + availableMoves - The Move class inner property,
 *                     maps a start position to a list of available moves.
 *                     It is fetched from the API at the beggining of the game,
 *                     and after the bot finishes its move.
 *  + availablePaths - A property of the Game component state,
 *                     it represents the available paths for the current chosen piece.
 */
export default class Move {

    constructor(game) {
        this.game = game;
        this.fetchAvailableMoves();
    }

    /**
     * Converts state.board to array of strings supported by API (swaps 'b' and 'w' characters).
     */
     convertStateToSend() {
        const boardToSend = this.game.state.board.map(row =>
            row.map(piece => piece === 'b' ? 'w' : (piece === 'w' ? 'b' : piece)));
        return boardToSend;
    }

    /**
     * Translate API's available moves to map of Position list.
     * It truncates the start positions from each move.
     * @param {*} receivedMove - available moves
     * @returns mapping of pretty strings representing start positions to list of Position list
     */
    convertAPIAvailableMoves(moves) {
        var res = {};
        Object.entries(moves).forEach(entry => {
            var [starting_pos, moves] = entry;
            res[starting_pos] = moves.map(move => this.convertAPIMove(move).slice(1));
        });
        return res;
    }

    /**
     * Convert API move to Position list
     * @param {*} receivedMove - API move in form of array of strings 
     * @returns Position list
     */
    convertAPIMove(move) {
        return move.map(pos => Position.fromPrettyString(pos));
    }

    /**
     * Fetches available moves from the API, converts it and saves as the property.
     */
    async fetchAvailableMoves() {
        fetch('/available_moves', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({
                'type': 'board',
                'state': this.convertStateToSend()
            })
        })
        .then(response => response.json())
        .then(data => this.convertAPIAvailableMoves(data.available_moves))
        .then(moves => { this.availableMoves = moves; });
    }

    /**
     * Fetches bot's move from the API, truncates the start position and returns Game's state.
     * @returns Game's state after choosing a piece
     */
    async chooseBotPiece() {
        return fetch('/bot_move', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({
              'type': 'board',
              'bot_name': this.game.state.chosenBot,
              'bot_parameters': {},
              'state': this.convertStateToSend()
            })
        })
        .then(response => response.json())
        .then(data => this.convertAPIMove(data.move))
        .then(move => {
            var [start_pos, ...move_truncated] = move;
            return ({
                ...this.game.state,
                chosenPiece: start_pos,
                availablePaths: [move_truncated]
            });
        });
    }

    /**
     * Returns available moves starting with given position.
     * @param {*} position - start position
     * @returns available paths for that position
     */
    getAvailablePaths(position) {
        return this.availableMoves[position.toPrettyString()] ?? [];
    }

    /**
     * Returns Game's state after choosing a piece.
     * @param {*} position - choosed position
     * @returns Game's state after choosing a piece
     */
    choosePiece(position) {
        return {
            ...this.game.state,
            chosenPiece: position,
            availablePaths: this.getAvailablePaths(position),
        };
    }

    /**
     * If exists, returns position of a piece captured by a jump.
     * Otherwise return null;
     * @param {*} oldPos - old position of a chosen piece
     * @param {*} newPos - new position of a chosen piece
     */
    #getCaptured(oldPos, newPos) {
        var axisDist = oldPos.axisDist(newPos);
        return (
            axisDist.x === 2 && axisDist.y === 2
            ? oldPos.middle(newPos)
            : null
        );
    }

    /**
     * Returns the state of the board after jump of chosen piece on newPos.
     * @param {*} newPos - new position of a chosen piece
     */
    #getBoardAfterJump(newPos) {
        var oldPos = this.game.getChosenPiece();
        var capturedPiece = this.#getCaptured(oldPos, newPos);
        
        return this.game.getBoard().map(
            (row, i) => row.map((el, j) =>
                (this.game.getChosenPiece().isEqual([i, j]) || Position.areEqual(capturedPiece, [i, j]))  
                ? '.'
                : newPos.isEqual([i, j])
                ? this.game.getActivePlayer()
                : el));
    }

    /**
     * Performs a single jump of a chosen piece on a given position.
     * @param {*} newPos - new position
     * @returns Returns the game state after jump.
     */
    jumpOn(newPos) {
        var board = this.#getBoardAfterJump(newPos);
        var activePlayer = this.game.getActivePlayer();
        var chosenPiece = newPos;
        var availablePaths = this.game.getAvailablePaths()
            .filter(([first, ..._]) => newPos.isEqual(first))
            .map(([_, ...rest]) => [...rest]);
        var pathTravelled = this.game.getPathTravelled().concat([this.game.getChosenPiece()]);

        /** If moved ended after this jump */
        if (availablePaths.every((move) => move.length === 0)) {
            activePlayer = this.game.getOpponent();
            chosenPiece = null;
            availablePaths = [];
            pathTravelled = [];
        }

        return {
            board: board,
            activePlayer: activePlayer,
            chosenPiece: chosenPiece,
            availablePaths: availablePaths,
            pathTravelled: pathTravelled
        };
    }
    
}