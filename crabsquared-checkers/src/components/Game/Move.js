import { PathsLoader } from "./PathsLoader";
import { Position } from "./Position";

/**
 * Class enabling control over move of a single piece. 
 */
export default class Move {
    constructor(game) {
        this.pathsLoader = new PathsLoader(game);
        this.startPos = this.currPos = null;
        this.availablePaths = [];
    }

    /**
     * Initializes move of a choosen piece.
     * @param {*} position - clicked position
     */
    choosePiece(position) {
        this.startPos = this.currPos = position;
        this.availablePaths = this.pathsLoader.getAvailablePaths(position);
    }

    /**
     * Initializes move from a game state.
     * @param {*} state - state of a game.
     */
    loadState(state) {
        this.startPos = this.currPos = state.chosenPiece;
        this.availablePaths = state.availablePaths;
    }

    /**
     * Path is a list of arrays of form [x, y] that represent
     * a move possible for a chosen piece.
     * @returns list of paths available for a chosen piece.
     */
    getAvailablePaths() {
        return this.availablePaths;
    }

    /**
     * Returns flattened list of available paths, i.e. list of arrays of form [x, y].
     */
    availableSquares() {
        return this.availablePaths ? this.availablePaths.flat() : null;
    }

    /**
     * Returns whether a move is in progress.
     * Move is in progress when current position and starting position are the same.(possibly null)
     */
    inProgress() {
        return !Position.areEqual(this.currPos, this.startPos);
    }

    /**
     * Performs a single jump of a chosen piece on a given position.
     * @param {*} newPos - new position
     * @returns If any piece was captured, its position. Otherwise null.
     */
    jumpOn(newPos) {
        var oldPos = this.currPos;
        var axisDist = oldPos.axisDist(newPos);
        var captured = axisDist.x === 2 && axisDist.y === 2 ? oldPos.middle(newPos) : null;
        
        this.currPos = newPos;
        this.availablePaths = this.availablePaths
            .filter(([first, ..._]) => newPos.isEqual(first))
            .map(([_, ...rest]) => [...rest]);

        if (this.availablePaths.every((move) => move.length === 0)) {
            this.startPos = this.currPos = null;
            this.availablePaths = [];
        }
        return captured;
    }
    
}