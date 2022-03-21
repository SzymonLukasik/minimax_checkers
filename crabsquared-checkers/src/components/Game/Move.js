import { PathsLoader } from "./PathsLoader";
import { Position } from "./Position";
import { cloneDeep } from "lodash";

/**
 * Class enabling control over move of a single piece. 
 */
export default class Move {
    constructor(game) {
        this.pathsLoader = new PathsLoader(game);
        this.chosenPiece = null
        this.availablePaths = [];
        this.pathTravelled = [];
    }

    /**
     * Initializes move of a choosen piece.
     * @param {*} position - clicked position
     */
    choosePiece(position) {
        this.chosenPiece = position;
        this.availablePaths = this.pathsLoader.getAvailablePaths(position);
        this.pathTravelled = []
    }

    /**
     * Initializes move from a game state.
     * @param {*} state - state of a game.
     */
    loadState(state) {
        this.chosenPiece = state.chosenPiece;
        this.availablePaths = state.availablePaths;
        this.pathTravelled = state.pathTravelled;
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
        return this.availablePaths ? this.availablePaths.flat() : [];
    }

    /**
     * Returns path travelled by currently chosen piece.
     */
    getPathTravelled() {
        return this.pathTravelled;
    }

    /**
     * Returns whether a move is in progress.
     * Move is in progress when path travelled is not empty.
     */
    inProgress() {
        return this.pathTravelled.length > 0;
    }

    /**
     * If exists, returns position of a piece captured by a jump.
     * Otherwise return null;
     * @param {*} oldPos - old position of a chosen piece
     * @param {*} newPos - new position of a chosen piece
     */
    getCaptured(oldPos, newPos) {
        var axisDist = oldPos.axisDist(newPos);
        return (
            axisDist.x === 2 && axisDist.y === 2
            ? oldPos.middle(newPos)
            : null
        );
    }

    /**
     * Performs a single jump of a chosen piece on a given position.
     * @param {*} newPos - new position
     * @returns If any piece was captured, its position. Otherwise null.
     */
    jumpOn(newPos) {
        var oldPos = this.chosenPiece;
        var captured = this.getCaptured(oldPos, newPos);
        
        this.chosenPiece = newPos;
        this.availablePaths = this.availablePaths
            .filter(([first, ..._]) => newPos.isEqual(first))
            .map(([_, ...rest]) => [...rest]);
        this.pathTravelled.push(oldPos);

        if (this.availablePaths.every((move) => move.length === 0)) {
            this.chosenPiece = null;
            this.availablePaths = [];
            this.pathTravelled = [];
        }

        return captured;
    }
    
}