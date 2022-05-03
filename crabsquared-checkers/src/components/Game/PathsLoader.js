/*eslint no-extend-native: ["error", { "exceptions": ["Array"] }]*/

import { Position } from "./Position";

/**
 * Enables genaration of possible paths for a given piece.
 * Possibly to be replaced by a module that communicates with engine.
 */
export class PathsLoader {
    constructor(game) {
        this.game = game;
    }

    /**
     * Returns a list of paths consisting of single position of form [x, y], that 
     * is a list representing possible non-capture moves.
     * @param {*} x - x-axis index
     * @param {*} y - y-axis index
     */
    #getNonCaptures(x, y) {
        var b, e;
        var player = this.game.getActivePlayer();
        if ((player === 'w' && x > 0) || (player === 'b' && x < 7)) {
            [b, e] = player === 'w' ? [x - 1, x] : [x + 1, x + 2];
            return this.game.getBoard()
                .slice(b, e)[0]
                .flatMap((el, j) => 
                    el === '.' && Math.abs(y - j) === 1
                    ? [[[b, j]]]
                    : []);
        }
        return [];
    }

    /**
     * Returns a list of single positions of form [x, y],
     * that is a list representing a possible single capture jumps.
     * @param {*} x - x-axis index
     * @param {*} y - y-axis index
     */
    #getSingleCaptures(x, y) {
        var player = this.game.getActivePlayer();
        if ((player === 'w' && x > 1) || (player === 'b' && x < 6)) {
            var opponent = this.game.getOpponent();
            var board = this.game.getBoard();
            var b, e;
            [b, e] = player === 'w' ? [x - 2, x - 1] : [x + 2, x + 3];
            return board
                .slice(b, e)[0]
                .flatMap((el, j) => 
                    (el === '.' && Math.abs(y - j) === 2
                    && board.atPosition(Position.middle([b, j], [x, y])) === opponent)
                    ? [[b, j]]
                    : []);
            }
        return [];
    }
    
    /**
     * Returns a list of possible capture moves.
     * @param {*} x - x-axis index
     * @param {*} y - y-axis index
     * @param {*} current_seq - current sequence of captures
     * @param {*} result - result array of possible paths
     */
    #getCaptures(x, y, current_seq, result) {
        var moves = this.#getSingleCaptures(x, y);
        if (moves.length === 0) {
            // capture ended, if sequence is not empty, we add it to the result  
            if (current_seq.length > 0) result.push(current_seq);
        } else {
            // we have to continue the capture, 
            //we consider each possibility and add the jump to the path
            moves.forEach(([i, j]) => 
                this.#getCaptures(i, j, current_seq.concat([[i, j]]), result));
        }
    }

    /**
     * Returns a list of possible paths.
     * If no captures paths are possible, returns non-capture paths.
     * Otherwise returns capture paths.
     * @param {*} position - chosen position
     */
    getAvailablePaths(position) {
        var x, y;
        [x, y] = [position.x, position.y];
        var res = []
        this.#getCaptures(x, y, [], res);
        if (res.length === 0) res = this.#getNonCaptures(x, y);
        return res;
    }
}