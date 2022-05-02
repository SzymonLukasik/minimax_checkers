import { PathsLoader } from "./PathsLoader";
import { Position } from "./Position";

/**
 * Class enabling control over move of a single piece. 
 */
export default class Move {
    constructor(game) {
        this.pathsLoader = new PathsLoader(game);
        this.game = game;
    }

    choosePiece(position) {
        return {
            ...this.game.state,
            chosenPiece: position,
            availablePaths: this.pathsLoader.getAvailablePaths(position)
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