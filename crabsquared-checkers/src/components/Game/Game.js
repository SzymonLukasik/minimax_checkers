import React from 'react';
import { cloneDeep } from 'lodash';
import './Game.css';

import Board from '../Board/Board';
import Move from './Move';
import { Position } from './Position';

export default class Game extends React.Component {
    constructor(props){
        super(props);
        this.state = {
            board: [
                ['c','-','c','-','c','-','c','-'],
                ['-','c','-','c','-','c','-','c'],
                ['c','-','c','-','c','-','c','-'],
                ['-','-','-','-','-','-','-','-'],
                ['-','-','-','-','-','-','-','-'],
                ['-','b','-','b','-','b','-','b'],
                ['b','-','b','-','b','-','b','-'],
                ['-','b','-','b','-','b','-','b']
            ],
            activePlayer: 'b',
            /** Position of a piece to be moved. */
            chosenPiece: null,
            /** List of paths that describes possible moves for a chosen piece. */
            availablePaths: null
        }
        this.handleSquareClick = this.handleSquareClick.bind(this);
        this.handleUndoClick = this.handleUndoClick.bind(this);

        /** Contains all game states previous to the current one. */
        this.history = [];
        this.move = new Move(this);
    }

    /**
     * Returns the opponent of the active player. 
     */
    getOpponent() {
        return this.state.activePlayer === 'b' ? 'c' : 'b';
    }

    /**
     * Handles a choose of a piece.
     * @param {*} position - clicked position
     * @returns whether a piece was choosen successfully
     */
    choosePiece(position) {
        if (this.state.board.atPosition(position) === this.state.activePlayer) {
            this.move.choosePiece(position);
            this.setState({
                ...this.state,
                chosenPiece: position,
                availablePaths: this.move.getAvailablePaths()
            });
            return true;
        }
        return false;
    }

    /**
     * Returns whether a piece was already chosen.
     */
    isPieceChosen() {
        return this.state.chosenPiece !== null;
    }

    /**
     * Checks whether a position is available to the chosen piece in a single jump.
     * It looks for a path that starts with a clicked position amongst available paths.
     * @param {*} position - clicked position
     */
    isAvailable(position) {
        return this.move.getAvailablePaths().some(([first, ..._]) => position.isEqual(first));
    }

    /**
     * Moves chosen piece to a clicked position if the position is available.
     * @param {*} position - clicked position
     */
    movePiece(position) {
        if (this.isAvailable(position)) {
            var captured = this.move.jumpOn(position);
            this.history.push(cloneDeep(this.state));
            this.setState(state => {
                return {
                    board: state.board.map(
                        (row, i) => row.map((el, j) =>
                            (this.state.chosenPiece.isEqual([i, j]) || Position.areEqual(captured, [i, j]))  
                            ? '-'
                            : position.isEqual([i, j]) 
                            ? state.activePlayer
                            : el)),
                    activePlayer: this.move.inProgress() ? state.activePlayer : this.getOpponent(),
                    count: state.count + 1,
                    chosenPiece:  this.move.inProgress() ? position : null,
                    availablePaths: this.move.getAvailablePaths()
                }
            });
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
        if (this.move.inProgress()
            || (!this.choosePiece(position) && this.isPieceChosen()))
            this.movePiece(position);
    }

    /**
     * Handles a undo button click.
     * If there was a state previous to the current, pops it out of the history,
     * initialize the move coordinator with it and sets it as the current state.
     */
    handleUndoClick() {
        if (this.history.length > 0) {
            var previousState = this.history.pop();
            this.move.loadState(previousState);
            this.setState(
                previousState,
                () =>this.move.choosePiece(previousState.chosenPiece)
            );
        }
    }

    renderBoard() {
        return (
            <Board board={this.state.board}
                   handleClick={this.handleSquareClick}
                   chosenPiece={this.state.chosenPiece}
                   availableSquares={this.move.availableSquares()}/>
        );
    }

    render() {
        return (
            <div className="game">
                <div className="game-board">
                    {this.renderBoard()}
                </div>
                <button className="undo-button"
                        onClick={this.handleUndoClick}>
                </button>
            </div>
        );
    }
}