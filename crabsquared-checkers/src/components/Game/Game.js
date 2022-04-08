import React from 'react';
import { cloneDeep } from 'lodash';
import './Game.css';

import Board from '../Board/Board';
import InfoPanel from '../InfoPanel/InfoPanel';
import Move from './Move';

export default class Game extends React.Component {
    constructor(props){
        super(props);
        this.state = {
            board: [
                ['b','-','b','-','b','-','b','-'],
                ['-','b','-','b','-','b','-','b'],
                ['b','-','b','-','b','-','b','-'],
                ['-','-','-','-','-','-','-','-'],
                ['-','-','-','-','-','-','-','-'],
                ['-','w','-','w','-','w','-','w'],
                ['w','-','w','-','w','-','w','-'],
                ['-','w','-','w','-','w','-','w']
            ],
            
            activePlayer: 'w',

            /** Position of a piece to be moved. */
            chosenPiece: null,

            /** List of paths that describes possible moves for a chosen piece. */
            availablePaths: null,

            /** Path of squares travelled by currently chosenPiece */
            pathTravelled: []
        }
        this.handleSquareClick = this.handleSquareClick.bind(this);
        this.handleUndoClick = this.handleUndoClick.bind(this);

        /** Contains all game states previous to the current one. */
        this.history = [];

        /** Helps handle moves. */
        this.move = new Move(this);
    }

    getBoard() {
        return this.state.board;
    }

    getActivePlayer() {
        return this.state.activePlayer;
    }

    getChosenPiece() {
        return this.state.chosenPiece;
    }

    getAvailablePaths() {
        return this.state.availablePaths;
    }

    getPathTravelled() {
        return this.state.pathTravelled;
    }

    /**
     * Returns the opponent of the active player. 
     */
    getOpponent() {
        return this.state.activePlayer === 'w' ? 'b' : 'w';
    }

    /**
     * Returns flattened list of available paths, i.e. list of arrays of form [x, y].
     */
    getAvailableSquares() {
        return this.state.availablePaths ? this.state.availablePaths.flat() : [];
    }

    /**
     * Returns whether a move is in progress.
     * Move is in progress when path travelled is not empty.
     */
    #isMoveInProgress() {
        return this.state.pathTravelled.length > 0;
    }

    /**
     * Handles a choose of a piece.
     * @param {*} position - clicked position
     * @returns whether a piece was choosen successfully
     */
    #choosePiece(position) {
        if (this.state.board.atPosition(position) === this.state.activePlayer) {
            this.setState(this.move.choosePiece(position));
            return true;
        }
        return false;
    }

    /**
     * Returns whether a piece was already chosen.
     */
    #isPieceChosen() {
        return this.state.chosenPiece !== null;
    }

    /**
     * Checks whether a position is available to the chosen piece in a single jump.
     * It looks for a path that starts with a clicked position amongst available paths.
     * @param {*} position - clicked position
     */
    #isAvailable(position) {
        return this.getAvailablePaths().some(([first, ..._]) => position.isEqual(first));
    }

    /**
     * Moves chosen piece to a clicked position if the position is available.
     * @param {*} position - clicked position
     */
    #movePiece(position) {
        if (this.#isAvailable(position)) {
            this.history.push(cloneDeep(this.state));
            this.setState(this.move.jumpOn(position));
        }
    }

    /**
     * Handles a square click.
     * If there is a move in progress tries to move chosen piece to the clicked position.
     * Otherwise, it tries to choose a piece (possibly replacing the current one)
     * and if the choose of a new piece was not successfull, if there already is a chosen piece,
     * it tries to move it to the clicked position (start the move).
     * @param {*} position - clicked position
     */
    handleSquareClick(position) {
        if (this.#isMoveInProgress()
            || (!this.#choosePiece(position) && this.#isPieceChosen()))
            this.#movePiece(position);
    }

    /**
     * Handles a undo button click.
     * If there was a state previous to the current, pops it out of the history,
     * initialize the move coordinator with it and sets it as the current state.
     */
    handleUndoClick() {
        if (this.history.length > 0) {
            var previousState = this.history.pop();
            this.setState(previousState);
        }
    }

    renderBoard() {
        return (
            <Board board={this.state.board}
                   handleClick={this.handleSquareClick}
                   chosenPiece={this.state.chosenPiece}
                   availableSquares={this.getAvailableSquares()}
                   pathTravelled={this.state.pathTravelled}/>
        );
    }

    render() {
        return (
            <div className="game">
                <div className="game-board">
                    {this.renderBoard()}
                </div>
                <InfoPanel 
                    handleUndoClick={this.handleUndoClick}
                    currentPlayer={this.state.activePlayer}
                />
            </div>
        );
    }
}